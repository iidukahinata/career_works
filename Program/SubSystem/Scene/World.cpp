/**
* @file    World.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
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
	camera->AddComponent("Camera");
	camera->AddComponent("AudioListener");
	camera->AddComponent("PostProcessEffect");

	auto directionalLight = CreateAndAddGameObject();
	directionalLight->AddComponent("Light");

	auto obj = CreateAndAddGameObject();
	obj->AddComponent("MeshRender");
	obj->AddComponent("AudioSpeaker");
}

void World::SaveScene(String_View sceneName) noexcept
{

}

GameObject* World::CreateAndAddGameObject() noexcept
{
	GameObject* result = nullptr;

	if (auto gameObject = GameObjectFactory::Create(this))
	{
		result = gameObject.Get();
		AddGameObject(gameObject.Release());
	}

	return result;
}

void World::AddGameObject(UniquePtr<GameObject> gameObject) noexcept
{
	if (gameObject)
	{
		gameObject->SetID(m_gameObjects.size());
		m_gameObjects.emplace_back(gameObject.Release());
	}
}

GameObject* World::GetGameObjectByName(String_View name) const noexcept
{
	for (const auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetName() == name)
		{
			return gameObject.Get();
		}
	}
	return nullptr;
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
	m_gameObjects[id].Reset(m_gameObjects.back().Release());

	// メモリ取得、解放が連続で起きるようなゲームにした場合、
	// 下記の処理をPopではなくGameObjectのデータクリアに変更し、再利用出来る様な仕様に変更するべき
	m_gameObjects.pop_back();
}

const Vector<UniquePtr<GameObject>>& World::GetGameObjects() noexcept
{
	return m_gameObjects;
}