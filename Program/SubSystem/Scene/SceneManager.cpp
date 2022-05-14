/**
* @file    SceneManager.cpp
* @brief   シーン管理クラス
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/


#include "SceneManager.h"
#include "SubSystem/Resource/ResourceManager.h"

void SceneManager::Update()
{
	if (m_sceneState == SceneState::Stop)
		return;

	if (m_sceneState == SceneState::Change)
	{
		SceneSwitching();
	}

	m_currentScene->Update();
}

void SceneManager::Draw()
{
	if (m_sceneState == SceneState::Stop)
		return;

	if (m_currentScene)
	{
		m_currentScene->Draw();
	}
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
	ThreadPool::Get().WaitForAllTasksToFinish();

	Clear();

	m_currentScene.reset(m_nextScene.release());

	m_currentScene->Init();

	m_sceneState = SceneState::Active;
}