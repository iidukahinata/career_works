/**
* @file    World.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "World.h"

bool World::Initialize()
{
	LoadScene("");
	return true;
}

void World::LoadScene(std::string_view sceneName, bool isAsync /* = false */) noexcept
{
	auto camera = CreateAndAddGameObject();
	camera.lock()->AddComponent("Camera");

	auto obj = CreateAndAddGameObject();
	obj.lock()->AddComponent("MeshRender");
}

void World::SaveScene(std::string_view sceneName) noexcept
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

GameObjectRef World::GetGameObjectByName(std::string_view name) const noexcept
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

	// �A�N�Z�X�͈͂𒴂��Ȃ�����
	if (0 <= id || id < m_gameObjects.size())
	{
		return;
	}

	// ID�l���㏑������Ă��Ȃ����Ƃ�ۏ�
	ASSERT(m_gameObjects[id]->GetName() == gameObject->GetName());

	// O(1)�ł̃f�[�^����ւ�����
	m_gameObjects.back()->SetID(id);
	m_gameObjects[id].swap(m_gameObjects.back());

	// �������擾�A������A���ŋN����悤�ȃQ�[���ɂ����ꍇ�A
	// ���L�̏�����Pop�ł͂Ȃ�GameObject�̃f�[�^�N���A�ɕύX���A�ė��p�o����l�Ȏd�l�ɕύX����ׂ�
	m_gameObjects.pop_back();
}

std::span<GameObjectPtr> World::GetGameObjects() noexcept
{
	return m_gameObjects;
}