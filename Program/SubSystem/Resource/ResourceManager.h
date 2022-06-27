/**
* @file    ResourceManager.h
* @brief
*
* @date	   2022/06/27 2022年度初版
*/
#pragma once


#include <map>
#include <mutex>
#include <memory>
#include "Resources/IResource.h"
#include "SubSystem/Core/ISubsystem.h"

typedef std::weak_ptr<IResource> ResourceRef;
typedef std::shared_ptr<IResource> ResourcePtr;

/**
* このクラスではデータ競合を引き起こさない。
*/
class ResourceManager : public ISubsystem
{
	SUB_CLASS(ResourceManager)
public:

	void Shutdown() override;

	void AddResource(ResourcePtr resource, std::string_view filePath) noexcept;

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
	ResourceRef GetResourceByName(std::string_view filePath) noexcept;

	/** 2022/04/17 Sceneを跨いで使用されるリソースデータを解放しないために実装 */
	void FreeUnusedResourceObjects() noexcept;

	void Clear() noexcept;

private:

	// * Type -> <ファイル名、リソースオブジェクト>
	std::map<std::string, ResourcePtr> m_resources;

	// * このクラス内での排他制御実現用
	std::mutex m_mutex;
};

template<class T>
FORCEINLINE T* ResourceManager::Load(std::string_view filePath) noexcept
{
	// 同じリソースを読み込まないために保持しているか調べる
	if (auto copyResource = GetResourceByName(filePath).lock())
	{
		return dynamic_cast<T*>(copyResource.get());
	}

	// 読み込み時間中に同じリソースを生成しないようにするために先に登録
	AddResource(std::make_shared<T>(), filePath);

	if (auto resource = GetResourceByName(filePath).lock())
	{
		if (resource->Load(filePath))
		{
			return dynamic_cast<T*>(resource.get());
		}
	}

	LOG_ERROR("resource 初期化に失敗しました。");
	return nullptr;
}