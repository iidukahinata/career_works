/**
* @file    GameScene.h
* @brief
*
* @date	   2022/06/02 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include"SubSystem/Scene/Scene.h"

class GameScene : public IScene
{
	void Awake() override;

	// ������
	void Init() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

	const char* GetName() override
	{
		return "Game";
	}
};