/**
* @file    ResourceManager.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "Resources/IResource.h"
#include "SubSystem/Core/ISubsystem.h"

/**
* ���̃N���X�ł̓f�[�^�����������N�����Ȃ��B
*/
class ResourceManager : public ISubsystem
{
	SUB_CLASS(ResourceManager)
public:

	void Shutdown() override;

	/**
	* �������\�[�X��ǂݍ��܂Ȃ����߂Ɏ���
	* @param filePath [����] ��������̃t�@�C�����ł���K�v������܂��B
	* @return �������ꂽ���\�[�X�|�C���^��Ԃ��܂��B
	*		  �w�薼�̃��\�[�X�ǂݍ��݂Ɏ��s����� nullptr��Ԃ��B
	*/
	template<class T>
	T* Load(String_View filePath) noexcept;

	/**
	* �ێ����Ă���f�[�^�Ɏw�薼�̃��\�[�X�����邩���ׂ�
	* @param filePath [����] ��������̃t�@�C�����ł���K�v������܂��B
	* @return �w�薼���ێ����郊�\�[�X�̏ꍇ���̃|�C���^��Ԃ��B
	*		  �w�薼�̃��\�[�X�f�[�^���Ȃ��ꍇ nullptr��Ԃ��B
	*/
	IResource* GetResourceByName(String_View filePath) noexcept;

	/** 2022/04/17 Scene���ׂ��Ŏg�p����郊�\�[�X�f�[�^��������Ȃ����߂Ɏ��� */
	void FreeUnusedResourceObjects() noexcept;

	void Clear() noexcept;

	void AddResource(UniquePtr<IResource> resource, String_View filePath) noexcept;

private:

	// * Type -> <�t�@�C�����A���\�[�X�I�u�W�F�N�g>
	Map<String, UniquePtr<IResource>> m_resources;

	// * ���̃N���X���ł̔r����������p
	std::mutex m_mutex;
};

template<class T>
FORCEINLINE T* ResourceManager::Load(String_View filePath) noexcept
{
	// �������\�[�X��ǂݍ��܂Ȃ����߂ɕێ����Ă��邩���ׂ�
	if (auto copyResource = GetResourceByName(filePath))
	{
		return dynamic_cast<T*>(copyResource);
	}

	// �ǂݍ��ݎ��Ԓ��ɓ������\�[�X�𐶐����Ȃ��悤�ɂ��邽�߂ɐ�ɓo�^
	AddResource(MakeUnique<T>(), filePath);

	if (auto resource = GetResourceByName(filePath))
	{
		if (resource->Load(filePath))
		{
			return dynamic_cast<T*>(resource);
		}
	}

	LOG_ERROR("resource �������Ɏ��s���܂����B");
	return nullptr;
}