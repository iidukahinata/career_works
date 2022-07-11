/**
* @file    ComponentFactory.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "ComponentFactory.h"

// Rendering
#include "../Component/Components/Camera.h"
#include "../Component/Components/Light.h"
#include "../Component/Components/RenderObject.h"
#include "../Component/Components/PostProcessEffect.h"

// Audio
#include "../Component/Components/AudioListener.h"
#include "../Component/Components/AudioSpeaker.h"

#define CASE_CREATE_ISA_COMPONENT(CLASS, NAME, COMPONENT) case GetHashFromCRC(NAME): COMPONENT = MakeUnique<CLASS>(); break;
#define CASE_CREATE_COMPONENT(CLASS, COMPONENT) case GET_HASH(CLASS): COMPONENT = MakeUnique<CLASS>(); break;

UniquePtr<IComponent> ComponentFactory::Create(GameObject* gameObject, StringView name) noexcept
{
    UniquePtr<IComponent> component;
    const ComponentType type(name);

    switch (type.Hash)
    {
    CASE_CREATE_COMPONENT(Light             , component);
    CASE_CREATE_COMPONENT(Camera            , component);
    CASE_CREATE_COMPONENT(MeshRender        , component);
    CASE_CREATE_COMPONENT(AudioListener     , component);
    CASE_CREATE_COMPONENT(AudioSpeaker      , component);
    CASE_CREATE_COMPONENT(PostProcessEffect , component);
    default: break;
    }

    if (component)
    {
        component->m_owner = gameObject;
    }

    return component;
}