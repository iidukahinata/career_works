/**
* @file    CreateScene.h
* @brief
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include"SubSystem/Scene/Scene.h"
#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Renderer/Drawings/Effect/Postprocessing.h"
#include "SubSystem/Renderer/Drawings/SkyBox/SkyBox.h"


class EditScene : public IScene
{
	// ������
	void Init() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

	const char* GetName() override
	{
		return "Edit";
	}

private:

	IGameObject* m_player;

	Postprocessing postprocessing;

	SkyBox skyBox;
};