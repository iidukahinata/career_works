/**
* @file    ResourceManager.cpp
* @brief
*
* @date	   2022/06/23 2022�N�x����
*/


#include "ResourceManager.h"

void ResourceManager::Shutdown()
{
	Clear();
}

void ResourceManager::FreeUnusedResourceObjects() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	std::erase_if(
		m_resources,
		[](const auto& resource)
		{
			// �Q�ƒl�� 0 �ȉ��̎��͎g�p����Ă��Ȃ����̂Ƃ��ď���
			return !resource.second || resource.second->GetRef() <= 0;
		}
	);
}

void ResourceManager::Clear() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_resources.clear();
}