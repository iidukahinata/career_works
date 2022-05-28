/**
* @file    GameScene.h
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


class GameScene : public IScene
{
	void Awake() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:

	Postprocessing postprocessing;

	SkyBox skyBox;
};