/**
* @file    ResourceManager.cpp
* @brief   ���\�[�X�Ǘ��N���X
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
*/


#include "ResourceManager.h"

void ResourceManager::FreeUnusedResourceObjects() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	std::erase_if(
		m_resources,
		[](const auto& resource)
		{
			// �Q�ƒl�� 0 �ȉ��̎��͎g�p����Ă��Ȃ����̂Ƃ��ď���
			return !resource.second || resource.second->GetRefreneceCount() <= 0;
		}
	);
}

void ResourceManager::Clear() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_resources.clear();
}