/**
* @file    RenderObject.cpp
* @brief
*
* @date	   2022/06/30 2022”N“x‰”Å
*/


#include "RenderObject.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Renderer/Renderer.h"

void RenderObject::Initialize()
{
	m_renderer = GetContext()->GetSubsystem<Renderer>();

	RegisterToRenderer();

	Do_Initialize();
}

void RenderObject::Remove()
{
	UnRegisterFromRenderer();

	Do_Remove();
}

void RenderObject::Active(bool active)
{
	if (IsActive() == active)
		return;

	IComponent::Active(active);
	if (active)
	{
		RegisterToRenderer();
	}
	else
	{
		UnRegisterFromRenderer();
	}
}

void RenderObject::RegisterToRenderer()
{
	ASSERT(m_renderer);
	m_renderer->RegisterRenderObject(this);
}

void RenderObject::UnRegisterFromRenderer()
{
	ASSERT(m_renderer);
	m_renderer->RemoveRenderObject(this);
}