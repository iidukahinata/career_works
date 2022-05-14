/**
* @file    CreateScene.h
* @brief   Scene作成クラス
*
* @date	   2021/02/01 2021年度初版
* @version 1.00
* @author  飯塚陽太
* @note
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

private:

	IGameObject* m_player;

	Postprocessing postprocessing;

	SkyBox skyBox;
};