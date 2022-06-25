/**
* @file    ComponentFactory.cpp
* @brief
*
* @date	   2022/06/25 2022îNìxèâî≈
*/


#include "ComponentFactory.h"
#include "Components/Transform.h"

#define CASE_CREATE_COMPONENT(CLASS, COMPONENT) case GET_HASH(CLASS): COMPONENT = std::make_shared<CLASS>(); break;

ComponentPtr ComponentFactory::Create(GameObject* gameObject, std::string_view name) noexcept
{
    ComponentPtr component;
    const ComponentType type(name);

    switch (type.Hash)
    {
    CASE_CREATE_COMPONENT(Transform, component)
    default: break;
    }

    component->m_owner = gameObject;
    return component;
}