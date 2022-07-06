/**
* @file    PostProcessEffect.cpp
* @brief
*
* @date	   2022/07/06 2022”N“x‰”Å
*/


#include "PostProcessEffect.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Renderer/Renderer.h"

void PostProcessEffect::Initialize()
{
	m_renderer = GetContext()->GetSubsystem<Renderer>();
	RegisterToRenderer();
}

void PostProcessEffect::Remove()
{
	OnRegisterFromRenderer();
}

void PostProcessEffect::Active(bool isActive)
{
	IComponent::Active(isActive);
	if (isActive)
	{
		RegisterToRenderer();
	}
	else
	{
		OnRegisterFromRenderer();
	}
}

void PostProcessEffect::RegisterToRenderer()
{
	m_renderer->RegisterPostProcess(this);
}

void PostProcessEffect::OnRegisterFromRenderer()
{
	m_renderer->OnRegisterPostProcess(this);
}