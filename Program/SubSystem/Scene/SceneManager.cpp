/**
* @file    SceneManager.cpp
* @brief   �V�[���Ǘ��N���X
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
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

	// �V�[�����ׂ��Ŏg�p����郊�\�[�X���c���Ă������� Clear�֐� �͎g�p���Ȃ�
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