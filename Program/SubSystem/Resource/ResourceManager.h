/**
* @file    ResourceManager.h
* @brief   リソース管理クラス
*
* @date	   2022/05/06 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <map>
#include <memory>
#include "Resources/IResource.h"

/**
* このクラスではデータ競合を引き起こさない。
*/
class ResourceManager
{
private:

	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = default;
	ResourceManager& operator=(const ResourceManager&) = default;

public:

	static ResourceManager& Get() noexcept
	{
		static ResourceManager instance;
		return instance;
	}

	/**
	* 同じリソースを読み込まないために実装
	* @param filePath [入力] 何かしらのファイル名である必要があります。
	* @return 生成されたリソースポインタを返します。
	*		  指定名のリソース読み込みに失敗すると nullptrを返す。
	*/
	template<class T>
	T* Load(std::string_view filePath) noexcept;

	/**
	* 保持しているデータに指定名のリソースがあるか調べる
	* @param filePath [入力] 何かしらのファイル名である必要があります。
	* @return 指定名が保持するリソースの場合そのポインタを返す。
	*		  指定名のリソースデータがない場合 nullptrを返す。
	*/
	template<class T>
	T* GetResourceByName(std::string_view filePath) noexcept;

	/** 2022/04/17 Sceneを跨いで使用されるリソースデータを解放しないために実装 */
	void FreeUnusedResourceObjects() noexcept;

	void Clear() noexcept;

private:

	// * Type -> <ファイル名、リソースオブジェクト>
	std::map<std::string, std::unique_ptr<IResource>> m_resources;

	// * このクラス内での排他制御実現用
	std::mutex m_mutex;
};

template<class T>
inline T* ResourceManager::Load(std::string_view filePath) noexcept
{
	if (filePath.empty())
		return nullptr;

	// 同じリソースを読み込まないために保持しているか調べる
	if (auto copyResource = GetResourceByName<T>(filePath.data())) 
	{
		copyResource->AddRefreneceCount();
		return copyResource;
	}

	// 読み込み時間中に同じリソースを生成しないようにするために先に登録
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		m_resources[filePath.data()] = std::make_unique<T>();
	}

	if (m_resources[filePath.data()])
	{
		if (m_resources[filePath.data()]->Load(filePath.data()))
		{
			m_resources[filePath.data()]->AddRefreneceCount();
			return dynamic_cast<T*>(m_resources[filePath.data()].get());
		}
	}
	return nullptr;
}

template<class T>
inline T* ResourceManager::GetResourceByName(std::string_view filePath) noexcept
{
	// 配列外にアクセスしないための判定
	if (m_resources.contains(filePath.data()))
	{
		return dynamic_cast<T*>(m_resources[filePath.data()].get());
	}
	return nullptr;
}