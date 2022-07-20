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

#include "Component/Components/Light.h"
void CreateLight(World* world, int numX, int numY, int numZ)
{
	auto light = world->CreateAndAddGameObject();
	light->AddComponent("Light");

	light->GetTransform().SetPosition(Math::Vector3(numX * 2, numY * 2, numZ * 2));

	auto com = light->GetComponent<Light>();
	com->SetLightType(LightType::PointLight);
	com->SetColor(Math::Vector4(1, 0, 0, 0));
	com->SetInfluenceRange(2);
	com->SetIntensity(5);
}

void World::LoadScene(StringView sceneName, bool isAsync /* = false */) noexcept
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

	for (size_t x = 0; x < 8; ++x)
	{
		for (size_t y = 0; y < 1; ++y)
		{
			for (size_t z = 0; z < 8; ++z)
			{
				CreateLight(this, x, y, z);
			}
		}
	}
}

void World::SaveScene(StringView sceneName) noexcept
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

GameObject* World::GetGameObjectByName(StringView name) const noexcept
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