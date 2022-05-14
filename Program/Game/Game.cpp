/**
* @file    Game.cpp
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/


#include "Game.h"
#include "SubSystem/Audio/Audio.h"
#include "SubSystem/Input/Input.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Resource/ResourceManager.h"

#include "Game/Scene/EditScene.h"
#include "Game/Scene/GameScene.h"

void Game::Init()
{
	Renderer::Get().Init();

	Input::Get().Init();

	Audio::Get().Init(64);

	// �����V�[���Z�b�g
	m_sceneManager.ChangeScene<GameScene>();
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