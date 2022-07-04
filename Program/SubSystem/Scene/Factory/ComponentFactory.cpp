/**
* @file    ComponentFactory.cpp
* @brief
*
* @date	   2022/07/01 2022�N�x����
*/


#include "ComponentFactory.h"

// Rendering
#include "../Component/Components/Camera.h"
#include "../Component/Components/Light.h"
#include "../Component/Components/RenderObject.h"

// Audio
#include "../Component/Components/AudioListener.h"
#include "../Component/Components/AudioSpeaker.h"

#define CASE_CREATE_COMPONENT(CLASS, COMPONENT) case GET_HASH(CLASS): COMPONENT = std::make_unique<CLASS>(); break;

ComponentPtr ComponentFactory::Create(GameObject* gameObject, std::string_view name) noexcept
{
    ComponentPtr component;
    const ComponentType type(name);

    switch (type.Hash)
    {
    CASE_CREATE_COMPONENT(Light             , component);
    CASE_CREATE_COMPONENT(Camera            , component);
    CASE_CREATE_COMPONENT(MeshRender        , component);
    CASE_CREATE_COMPONENT(AudioListener     , component);
    CASE_CREATE_COMPONENT(AudioSpeaker      , component);
    default: break;
    }

    if (component)
    {
        component->m_owner = gameObject;
    }

    return component;
}