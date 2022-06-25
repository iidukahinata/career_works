/**
* @file    ComponentFactory.cpp
* @brief
*
* @date	   2022/06/25 2022”N“x‰”Å
*/


#include "ComponentFactory.h"

ComponentPtr ComponentFactory::Create(GameObject* gameObject, std::string_view name) noexcept
{
    ComponentPtr component;

    component->m_owner = gameObject;

    return component;
}