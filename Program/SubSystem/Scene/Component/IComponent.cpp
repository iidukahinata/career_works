/**
* @file    IComponent.cpp
* @brief
*
* @date	   2022/06/24 2022”N“x‰”Å
*/


#include "IComponent.h"

const ComponentType& IComponent::GetType()
{
	return ComponentType("IComponent");
}

GameObject* IComponent::GetOwner() const noexcept
{
	return m_owner;
}