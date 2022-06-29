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
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		if (it->second.get() == component)
		{
			component->Remove();
			m_components.erase(it);
			break;
		}
	}
}

IComponent* GameObject::FindComponent(std::string_view name) const noexcept
{
	const ComponentType type(name);
	for (const auto& component : m_components)
	{
		if (component.second->GetTypeData() == type)
		{
			return component.second.get();
		}
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