/**
* @file    World.cpp
* @brief
*
* @date	   2022/06/30 2022年度初版
*/


#include "World.h"
#include "TickManager.h"
#include "Factory/GameObjectFactory.h"

World::World()
{
	m_job.SetFunction([](double deltaTime) { TickManager::Get().Tick(deltaTime); }, FunctionType::Update);
	m_job.RegisterToJobSystem();
}

bool World::Initialize()
{
	LoadScene("");
	return true;
}

void World::Shutdown()
{
	m_job.UnRegisterFromJobSystem();
}

void World::LoadScene(String_View sceneName, bool isAsync /* = false */) noexcept
{
	auto camera = CreateAndAddGameObject();
	camera.lock()->AddComponent("Camera");
	camera.lock()->AddComponent("AudioListener");
	camera.lock()->AddComponent("PostProcessEffect");

	auto directionalLight = CreateAndAddGameObject();
	camera.lock()->AddComponent("Light");

	auto obj = CreateAndAddGameObject();
	obj.lock()->AddComponent("MeshRender");
	obj.lock()->AddComponent("AudioSpeaker");
}

void World::SaveScene(String_View sceneName) noexcept
{

}

GameObjectRef World::CreateAndAddGameObject() noexcept
{
	auto gameObject = GameObjectFactory::Create(this);
	AddGameObject(gameObject);
	return gameObject;
}

void World::AddGameObject(GameObjectPtr gameObject) noexcept
{
	if (gameObject)
	{
		gameObject->SetID(m_gameObjects.size());
		m_gameObjects.emplace_back(gameObject);
	}
}

GameObjectRef World::GetGameObjectByName(String_View name) const noexcept
{
	for (const auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetName() == name)
		{
			return gameObject;
		}
	}
	return GameObjectRef();
}

void World::RemoveGameObject(GameObject* gameObject) noexcept
{
	int id = gameObject->GetID();

	// アクセス範囲を超えないため
	if (0 <= id || id < m_gameObjects.size())
	{
		return;
	}

	// ID値が上書きされていないことを保証
	ASSERT(m_gameObjects[id]->GetName() == gameObject->GetName());

	// O(1)でのデータ入れ替え処理
	m_gameObjects.back()->SetID(id);
	m_gameObjects[id].swap(m_gameObjects.back());

	// メモリ取得、解放が連続で起きるようなゲームにした場合、
	// 下記の処理をPopではなくGameObjectのデータクリアに変更し、再利用出来る様な仕様に変更するべき
	m_gameObjects.pop_back();
}

const Vector<GameObjectPtr>& World::GetGameObjects() noexcept
{
	return m_gameObjects;
}