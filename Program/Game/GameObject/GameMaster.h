/**
* @file    GameMaster.cpp
* @brief
*
* @date	   2022/06/08 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"


class GameMaster : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Update() override;

	const char* GetName() override;

	// 各シーンごとにアクセスされめ作成。
	int& LoadWorldNum() noexcept;
	int& LoadStageNum() noexcept;

private:

	void TitleUpdate() noexcept;
	void SelectUpdate() noexcept;
	void GameUpdate() noexcept;
	void EditUpdate() noexcept;

private:

	enum class NowScene
	{
		Title,
		Select,
		Game,
		Edit,
		None,
	};

	NowScene m_nowScene = NowScene::None;

	static const int maxWorldNum = 6;
	static const int maxStageNum = 5;
};