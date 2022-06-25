/**
* @file    GameObject.cpp
* @brief
*
* @date	   2022/06/24 2022”N“x‰”Å
*/


#include "GameObject.h"
#include "World.h"
#include "Component/ComponentFactory.h"

IComponent* GameObject::AddComponent(std::string_view name) noexcept
{
	IComponent* result = nullptr;

	if (auto component = ComponentFactory::Create(this, name))
	{
		auto hash = component->GetType().Hash;
		m_components[hash] = component;
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
			m_components.erase(it);
			break;
		}
	}
}

IComponent* GameObject::FindComponent(std::string_view name) const noexcept
{
	const ComponentType type(name);
	for (auto& component : m_components)
	{
		if (component.second->GetType() == type)
		{
			return component.second.get();
		}
	}
	return nullptr;
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

std::string_view GameObject::GetName() const noexcept
{
	return m_name;
}

//Transform* GameObject::GetTransform() noexcept
//{
//	return m_transform;
//}

World* GameObject::GetOwner() const noexcept
{
	return m_owner;
}

Context* GameObject::GetContext() const noexcept
{
	return m_owner ? m_owner->GetContext() : nullptr;
}