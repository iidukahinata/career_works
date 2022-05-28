/**
* @file    SceneManager.cpp
* @brief   �V�[���Ǘ��N���X
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "SceneManager.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Tools/Chack.h"

void SceneManager::Update()
{
	Chack(m_sceneState != SceneState::Stop, "Scene ���Z�b�g����Ă��܂���B");

	if (m_sceneState == SceneState::Change)
	{
		SceneSwitching();
	}

	m_currentScene->Update();
}

void SceneManager::Draw()
{
	Chack(m_sceneState != SceneState::Stop, "Scene ���Z�b�g����Ă��܂���B");

	m_currentScene->Draw();
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
	// ���̋@�\�� ThreadPool ���g�p���Ă���ꍇ�A�����ɂ���Ă͖������[�v�ɓ���댯��������B
	ThreadPool::Get().WaitForAllTasksToFinish();

	Clear();

	m_currentScene.reset(m_nextScene.release());

	m_currentScene->Init();

	m_sceneState = SceneState::Active;
}