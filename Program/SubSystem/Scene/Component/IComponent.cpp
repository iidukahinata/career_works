/**
* @file    IComponent.cpp
* @brief
*
* @date	   2022/06/30 2022”N“x‰”Å
*/


#include "IComponent.h"
#include "../GameObject.h"

void TickComponentFunction::Tick(double deltaTime)
{
	m_component->Update(deltaTime);
}

IComponent::IComponent()
{
	m_tickFunction.m_component = this;
}

void IComponent::Active(bool active)
{
	m_active = active;

	SetTickEnable(active);
}

bool IComponent::IsActive() const noexcept
{
	return m_active;
}

void IComponent::SetTickEnable(bool enable) noexcept
{
	m_tickFunction.SetEnable(enable);
}

void IComponent::SetTickPriority(uint32_t priority) noexcept
{
	m_tickFunction.SetPriority(priority);
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