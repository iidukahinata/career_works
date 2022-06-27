/**
* @file    ResourceManager.h
* @brief
*
* @date	   2022/06/27 2022�N�x����
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
* ���̃N���X�ł̓f�[�^�����������N�����Ȃ��B
*/
class ResourceManager : public ISubsystem
{
	SUB_CLASS(ResourceManager)
public:

	void Shutdown() override;

	void AddResource(ResourcePtr resource, std::string_view filePath) noexcept;

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
	ResourceRef GetResourceByName(std::string_view filePath) noexcept;

	/** 2022/04/17 Scene���ׂ��Ŏg�p����郊�\�[�X�f�[�^��������Ȃ����߂Ɏ��� */
	void FreeUnusedResourceObjects() noexcept;

	void Clear() noexcept;

private:

	// * Type -> <�t�@�C�����A���\�[�X�I�u�W�F�N�g>
	std::map<std::string, ResourcePtr> m_resources;

	// * ���̃N���X���ł̔r����������p
	std::mutex m_mutex;
};

template<class T>
FORCEINLINE T* ResourceManager::Load(std::string_view filePath) noexcept
{
	// �������\�[�X��ǂݍ��܂Ȃ����߂ɕێ����Ă��邩���ׂ�
	if (auto copyResource = GetResourceByName(filePath).lock())
	{
		return dynamic_cast<T*>(copyResource.get());
	}

	// �ǂݍ��ݎ��Ԓ��ɓ������\�[�X�𐶐����Ȃ��悤�ɂ��邽�߂ɐ�ɓo�^
	AddResource(std::make_shared<T>(), filePath);

	if (auto resource = GetResourceByName(filePath).lock())
	{
		if (resource->Load(filePath))
		{
			return dynamic_cast<T*>(resource.get());
		}
	}

	LOG_ERROR("resource �������Ɏ��s���܂����B");
	return nullptr;
}