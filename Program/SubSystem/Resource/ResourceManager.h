/**
* @file    ResourceManager.h
* @brief   ���\�[�X�Ǘ��N���X
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <map>
#include <memory>
#include "Resources/IResource.h"

/**
* ���̃N���X�ł̓f�[�^�����������N�����Ȃ��B
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
	* �������\�[�X��ǂݍ��܂Ȃ����߂Ɏ���
	* @param filePath [����] ��������̃t�@�C�����ł���K�v������܂��B
	* @return �������ꂽ���\�[�X�|�C���^��Ԃ��܂��B
	*		  �w�薼�̃��\�[�X�ǂݍ��݂Ɏ��s����� nullptr��Ԃ��B
	*/
	template<class T>
	T* Load(std::string_view filePath) noexcept;

	/**
	* �ێ����Ă���f�[�^�Ɏw�薼�̃��\�[�X�����邩���ׂ�
	* @param filePath [����] ��������̃t�@�C�����ł���K�v������܂��B
	* @return �w�薼���ێ����郊�\�[�X�̏ꍇ���̃|�C���^��Ԃ��B
	*		  �w�薼�̃��\�[�X�f�[�^���Ȃ��ꍇ nullptr��Ԃ��B
	*/
	template<class T>
	T* GetResourceByName(std::string_view filePath) noexcept;

	/** 2022/04/17 Scene���ׂ��Ŏg�p����郊�\�[�X�f�[�^��������Ȃ����߂Ɏ��� */
	void FreeUnusedResourceObjects() noexcept;

	void Clear() noexcept;

private:

	// * Type -> <�t�@�C�����A���\�[�X�I�u�W�F�N�g>
	std::map<std::string, std::unique_ptr<IResource>> m_resources;

	// * ���̃N���X���ł̔r����������p
	std::mutex m_mutex;
};

template<class T>
inline T* ResourceManager::Load(std::string_view filePath) noexcept
{
	if (filePath.empty())
		return nullptr;

	// �������\�[�X��ǂݍ��܂Ȃ����߂ɕێ����Ă��邩���ׂ�
	if (auto copyResource = GetResourceByName<T>(filePath.data())) 
	{
		copyResource->AddRefreneceCount();
		return copyResource;
	}

	// �ǂݍ��ݎ��Ԓ��ɓ������\�[�X�𐶐����Ȃ��悤�ɂ��邽�߂ɐ�ɓo�^
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
	// �z��O�ɃA�N�Z�X���Ȃ����߂̔���
	if (m_resources.contains(filePath.data()))
	{
		return dynamic_cast<T*>(m_resources[filePath.data()].get());
	}
	return nullptr;
}