/**
* @file    Scene.cpp
* @brief   �V�[�����ۃN���X
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/


#include "Scene.h"
#include "SceneManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"

void IScene::Update()
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->Update();
	}
}

void IScene::Draw()
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->Draw();
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
	if (!gameObject)
		return;

	// �������Ԃ̒Z�k�̂��߂ɔz��ԍ���ID�Ƃ���
	gameObject->SetID(m_gameObjects.size());
	gameObject->SetScene(this);

	gameObject->Init();

	m_gameObjects.emplace_back(gameObject);
}

IGameObject* IScene::GetGameObject(std::string_view name)
{
	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetName().c_str() == name.data())
			return gameObject.get();
	}
	return nullptr;
}

void IScene::RemoveGameObject(int id)
{
	if (id < 0 || m_gameObjects.size() <= id)
		return;

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
	assert(!m_sceneManager);
	m_sceneManager = sceneManager;
}