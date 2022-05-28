/**
* @file    Game.cpp
* @brief
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/


#include "Game.h"
#include "SubSystem/Audio/Audio.h"
#include "SubSystem/Input/Input.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Resource/ResourceManager.h"

#include "Game/Scene/TitleScene.h"

void Game::Init()
{
	Renderer::Get().Init();

	Input::Get().Init();

	Audio::Get().Init(64);

	// 初期シーンセット
	m_sceneManager.ChangeScene<TitleScene>();
}

void Game::Update(double deltatime)
{
	Input::Get().Update();

	Audio::Get().Update();

	m_sceneManager.Update();
}

void Game::Render(double deltatime)
{
	Renderer::Get().BeginFream();

	m_sceneManager.Draw();

	Renderer::Get().EndFream();
}

void Game::Exit()
{
	m_sceneManager.Clear();

	ResourceManager::Get().Clear();

	Renderer::Get().Exit();
}