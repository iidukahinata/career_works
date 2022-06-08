/**
* @file    CreateScene.h
* @brief
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include"SubSystem/Scene/Scene.h"
#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Renderer/Drawings/Effect/Postprocessing.h"
#include "SubSystem/Renderer/Drawings/SkyBox/SkyBox.h"


class EditScene : public IScene
{
	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
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