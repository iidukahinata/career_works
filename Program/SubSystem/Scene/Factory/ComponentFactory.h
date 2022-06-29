/**
* @file    ComponentFactory.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include <memory>
#include "../Component/IComponent.h"

typedef std::unique_ptr<IComponent> ComponentPtr;

/**
* �R���|�[�l���g�̐������V�X�e�����番�������邽�߂ɍ쐬�B
* ���̃N���X���g�p���Ȃ��ꍇ�AGameObject�|�C���^��ێ����Ȃ��I�u�W�F�N�g�f�[�^�ɂȂ�܂��B
* �V�����R���|�[�l���g���쐬�����ꍇ�A���L�֐����ɒǉ����Ă����B
*/
struct ComponentFactory
{
	static ComponentPtr Create(GameObject* gameObject, std::string_view name) noexcept;
};