/**
* @file    IComponent.cpp
* @brief
*
* @date	   2022/06/25 2022”N“x‰”Å
*/


#include "IComponent.h"
#include "../GameObject.h"

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