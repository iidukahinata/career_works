/**
* @file    Scene.cpp
* @brief   シーン抽象クラス
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/


#include "Scene.h"
#include "SceneManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Tools/Chack.h"

void IScene::Init()
{
	// 初期化中に GameObject が追加された場合 範囲 for だとアクセスバグが発生する。
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Init();
	}
}

void IScene::Update()
{
	// 初期化中に GameObject が追加された場合 範囲 for だとアクセスバグが発生する。
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
	// 検索時間の短縮のために配列番号をIDとする
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

	// O(1)でのデータ入れ替え処理
	m_gameObjects.back()->SetID(id);
	m_gameObjects[id].swap(m_gameObjects.back());

	// 指定IDデータを消去
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