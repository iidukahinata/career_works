/**
* @file    ComponentFactory.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "../Component/IComponent.h"

/**
* �R���|�[�l���g�̐������V�X�e�����番�������邽�߂ɍ쐬�B
* ���̃N���X���g�p���Ȃ��ꍇ�AGameObject�|�C���^��ێ����Ȃ��I�u�W�F�N�g�f�[�^�ɂȂ�܂��B
* �V�����R���|�[�l���g���쐬�����ꍇ�A���L�֐����ɒǉ����Ă����B
*/
struct ComponentFactory
{
	static UniquePtr<IComponent> Create(GameObject* gameObject, StringView name) noexcept;
};