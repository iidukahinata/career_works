/**
* @file    GameObjectFactory.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include <memory>
#include "GameObject.h"

typedef std::weak_ptr<GameObject> GameObjectRef;
typedef std::shared_ptr<GameObject> GameObjectPtr;

/**
* �Q�[���I�u�W�F�N�g�̐������V�X�e�����番�������邽�߂ɍ쐬�B
* ���̃N���X���g�p���Ȃ��ꍇ�AWorld�|�C���^��ێ����Ȃ��I�u�W�F�N�g�f�[�^�ɂȂ�܂��B
*/
struct GameObjectFactory
{
	static GameObjectPtr Create(World* world);
};