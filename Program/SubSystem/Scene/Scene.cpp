/**
* @file    Scene.cpp
* @brief   �V�[�����ۃN���X
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "Scene.h"
#include "SceneManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Tools/Chack.h"

void IScene::Init()
{
	// ���������� GameObject ���ǉ����ꂽ�ꍇ �͈� for ���ƃA�N�Z�X�o�O����������B
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Init();
	}
}

void IScene::Update()
{
	// ���������� GameObject ���ǉ����ꂽ�ꍇ �͈� for ���ƃA�N�Z�X�o�O����������B
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Update();
	}
}

void IScene::Draw()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Draw();
	}
}

void IScene::Clear()
{
	m_lightMap.Clear();
	m_gameObjects.clear();
	m_gameObjects.shrink_to_fit();
}

void IScene::AddGameObject(IGameObject* gameObject)
{
	// �������Ԃ̒Z�k�̂��߂ɔz��ԍ���ID�Ƃ���
	gameObject->SetID(m_gameObjects.size());
	gameObject->SetScene(this);

	gameObject->Awake();

	m_gameObjects.emplace_back(gameObject);
}

IGameObject* IScene::GetGameObject(std::string_view name)
{
	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetName() == name.data())
			return gameObject.get();
	}
	return nullptr;
}

void IScene::RemoveGameObject(IGameObject* gameObject)
{
	int id = gameObject->GetID();

	Chack(id >= 0);
	Chack(id < m_gameObjects.size());

	// O(1)�ł̃f�[�^����ւ�����
	m_gameObjects.back()->SetID(id);
	m_gameObjects[id].swap(m_gameObjects.back());

	// �w��ID�f�[�^������
	m_gameObjects.pop_back();
}

std::vector<std::unique_ptr<IGameObject>>& IScene::GetGameObjects() noexcept
{
	return m_gameObjects;
}

Camera* IScene::GetMainCamera() const noexcept
{
	return m_mainCamera.get();
}

LightMap* IScene::GetLightMap() noexcept
{
	return &m_lightMap;
}

void IScene::SetSceneManager(SceneManager* sceneManager) noexcept
{
	Chack(!m_sceneManager);
	m_sceneManager = sceneManager;
}