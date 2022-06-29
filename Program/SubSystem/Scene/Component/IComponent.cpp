/**
* @file    IComponent.cpp
* @brief
*
* @date	   2022/06/29 2022”N“x‰”Å
*/


#include "IComponent.h"
#include "../GameObject.h"

void IComponent::Active(bool active)
{
	m_active = active;
}

bool IComponent::IsActive() const noexcept
{
	return m_active;
}

Transform& IComponent::GetTransform() const noexcept
{
	ASSERT(m_owner);
	return m_owner->GetTransform();
}

GameObject* IComponent::GetOwner() const noexcept
{
	return m_owner;
}

World* IComponent::GetWorld() const noexcept
{
	ASSERT(m_owner);
	return m_owner->GetOwner();
}

Context* IComponent::GetContext() const noexcept
{
	ASSERT(m_owner);
	return m_owner->GetContext();
}