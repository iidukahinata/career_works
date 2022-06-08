/**
* @file    GameScene.h
* @brief
*
* @date	   2022/06/02 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include"SubSystem/Scene/Scene.h"

class GameScene : public IScene
{
	void Awake() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	const char* GetName() override
	{
		return "Game";
	}
};