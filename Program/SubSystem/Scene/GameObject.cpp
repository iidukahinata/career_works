/**
* @file    GameObject.cpp
* @brief
*
* @date	   2022/06/29 2022”N“x‰”Å
*/


#include "GameObject.h"
#include "World.h"
#include "Factory/ComponentFactory.h"

IComponent* GameObject::AddComponent(std::string_view name) noexcept
{
	IComponent* result = nullptr;

	if (auto component = ComponentFactory::Create(this, name))
	{
		component->Initialize();

		auto hash = component->GetTypeData().Hash;
		m_components.emplace(hash, component.release());
		result = component.get();
	}

	return result;
}

void GameObject::RemoveComponent(IComponent* component) noexcept
{
	auto hash = component->GetTypeData().Hash;
	if (m_components.contains(hash))
	{
		component->Remove();
		m_components.erase(hash);
	}
}

IComponent* GameObject::FindComponent(std::string_view name) noexcept
{
	const ComponentType type(name);
	if (m_components.contains(type.Hash))
	{
		return m_components[type.Hash].get();
	}
	return nullptr;
}

void GameObject::Active(bool active) noexcept
{

}

uint32_t GameObject::GetID() const noexcept
{
	return m_id;
}

void GameObject::SetID(uint32_t id) noexcept
{
	ASSERT(id >= 0);
	m_id = id;
}

void GameObject::SetName(std::string_view name) noexcept
{
	m_name = name;
}

const std::string& GameObject::GetName() const noexcept
{
	return m_name;
}


Transform& GameObject::GetTransform() const noexcept
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