/**
* @file    GameObjectFactory.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "../GameObject.h"

typedef UniquePtr<GameObject> GameObjectPtr;

/**
* �Q�[���I�u�W�F�N�g�̐������V�X�e�����番�������邽�߂ɍ쐬�B
* ���̃N���X���g�p���Ȃ��ꍇ�AWorld�|�C���^��ێ����Ȃ��I�u�W�F�N�g�f�[�^�ɂȂ�܂��B
*/
struct GameObjectFactory
{
	static GameObjectPtr Create(World* world);
};