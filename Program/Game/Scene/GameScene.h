/**
* @file    GameScene.h
* @brief   GameScene�N���X
*
* @date	   2021/02/01 2021�N�x����
* @version 1.00
* @author  �ђ˗z��
* @note
*/
#pragma once


#include"SubSystem/Scene/Scene.h"
#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Renderer/Drawings/Effect/Postprocessing.h"
#include "SubSystem/Renderer/Drawings/SkyBox/SkyBox.h"


class GameScene : public IScene
{
	void Awake() override;

	// ������
	void Init() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

private:

	IGameObject* m_player;

	Postprocessing postprocessing;

	SkyBox skyBox;
};