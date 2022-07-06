/**
* @file    ResourceManager.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "ResourceManager.h"
#include "Resources/3DModel/Material.h"

void ResourceManager::Shutdown()
{
	Clear();
}

void ResourceManager::AddResource(ResourcePtr resource, String_View filePath) noexcept
{
	ASSERT(!m_resources.contains(filePath.data()));

	std::unique_lock<std::mutex> lock(m_mutex);
	m_resources[filePath.data()].Reset(resource.Release());
}

IResource* ResourceManager::GetResourceByName(String_View filePath) noexcept
{
	// 配列外にアクセスしないための判定
	if (m_resources.contains(filePath.data()))
	{
		return m_resources[filePath.data()].Get();
	}
	return nullptr;
}

void ResourceManager::FreeUnusedResourceObjects() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	std::erase_if(
		m_resources,
		[](const auto& resource)
		{
			// 参照値が 0 以下の時は使用されていないものとして処理
			return !resource.second;
		}
	);
}

void ResourceManager::Clear() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_resources.clear();
}