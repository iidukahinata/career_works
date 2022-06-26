/**
* @file    ResourceManager.h
* @brief
*
* @date	   2022/06/23 2022年度初版
*/
#pragma once


#include <map>
#include <mutex>
#include <memory>
#include "Resources/IResource.h"
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/Core/Common/Common.h"

/**
* このクラスではデータ競合を引き起こさない。
*/
class ResourceManager : public ISubsystem
{
	SUB_CLASS(ResourceManager)
public:

	void Shutdown() override;

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
	// 同じリソースを読み込まないために保持しているか調べる
	if (auto copyResource = GetResourceByName<T>(filePath.data())) 
	{
		copyResource->AddRef();
		return copyResource;
	}

	// 読み込み時間中に同じリソースを生成しないようにするために先に登録
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		m_resources[filePath.data()] = std::make_unique<T>();
	}

	if (auto& resource = m_resources[filePath.data()])
	{
		if (resource->Load(filePath.data()))
		{
			resource->AddRef();
			return dynamic_cast<T*>(resource.get());
		}
	}

	LOG_ERROR("resource pointer の取得に失敗しました。");
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