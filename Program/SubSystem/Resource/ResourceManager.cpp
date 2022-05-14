/**
* @file    ResourceManager.cpp
* @brief   リソース管理クラス
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/


#include "ResourceManager.h"

void ResourceManager::FreeUnusedResourceObjects() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	std::erase_if(
		m_resources,
		[](const auto& resource)
		{
			// 参照値が 0 以下の時は使用されていないものとして処理
			return !resource.second || resource.second->GetRefreneceCount() <= 0;
		}
	);
}

void ResourceManager::Clear() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_resources.clear();
}