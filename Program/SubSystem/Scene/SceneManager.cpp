/**
* @file    SceneManager.cpp
* @brief   シーン管理クラス
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/


#include "SceneManager.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Tools/Chack.h"

void SceneManager::Update()
{
	Chack(m_sceneState != SceneState::Stop, "Scene がセットされていません。");

	if (m_sceneState == SceneState::Change)
	{
		SceneSwitching();
	}

	m_currentScene->Update();
}

void SceneManager::Draw()
{
	Chack(m_sceneState != SceneState::Stop, "Scene がセットされていません。");

	m_currentScene->Draw();
}

void SceneManager::Clear()
{
	if (m_currentScene)
	{
		m_currentScene->Clear();
	}

	m_currentScene.reset();

	// シーンを跨いで使用されるリソースを残しておくため Clear関数 は使用しない
	ResourceManager::Get().FreeUnusedResourceObjects();
}

void SceneManager::SceneSwitching()
{
	// 他の機能が ThreadPool を使用している場合、処理によっては無限ループに入る危険性がある。
	ThreadPool::Get().WaitForAllTasksToFinish();

	Clear();

	m_currentScene.reset(m_nextScene.release());

	m_currentScene->Init();

	m_sceneState = SceneState::Active;
}