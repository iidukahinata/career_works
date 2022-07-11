/**
* @file    GameObject.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "GameObject.h"
#include "World.h"
#include "Factory/ComponentFactory.h"

IComponent* GameObject::AddComponent(StringView name) noexcept
{
	IComponent* result = nullptr;

	if (auto component = ComponentFactory::Create(this, name))
	{
		result = component.Get();
		AddComponent(component.Release());
	}

	return result;
}

void GameObject::AddComponent(IComponent* component) noexcept
{
	const auto hash = component->GetTypeData().Hash;

	if (m_components.contains(hash))
	{
		LOG_ERROR("既に同じHash値のコンポーネントが存在しています。");
	}
	else
	{
		component->Initialize();
		m_components.emplace(hash, component);
	}
}

void GameObject::RemoveComponent(IComponent* component) noexcept
{
	const auto hash = component->GetTypeData().Hash;
	if (m_components.contains(hash))
	{
		component->Remove();
		m_components.erase(hash);
	}
}

IComponent* GameObject::FindComponent(StringView name) noexcept
{
	const ComponentType type(name);
	if (m_components.contains(type.Hash))
	{
		return m_components[type.Hash].Get();
	}
	return nullptr;
}

uint32_t GameObject::GetID() const noexcept
{
	return m_id;
}

void GameObject::AddTickComponent(IComponent* component) noexcept
{

}

void GameObject::RemoveTickComponent(IComponent* component) noexcept
{

}

void GameObject::SetID(uint32_t id) noexcept
{
	ASSERT(id >= 0);
	m_id = id;
}

void GameObject::SetName(StringView name) noexcept
{
	m_name = name;
}

const String& GameObject::GetName() const noexcept
{
	return m_name;
}

Transform& GameObject::GetTransform() noexcept
{
	return m_transform;
}

World* GameObject::GetOwner() const noexcept
{
	return m_owner;
}

Context* GameObject::GetContext() const noexcept
{
	ASSERT(m_owner);
	return m_owner->GetContext();
}