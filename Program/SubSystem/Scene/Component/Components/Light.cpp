/**
* @file    Light.h
* @brief
*
* @date	   2022/06/27 2022”N“x‰”Å
*/


#include "Light.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Renderer/LightMap.h"

void Light::Initialize() 
{
	GetContext()->GetSubsystem<Renderer>()->GetLightMap().AddLight(this);

	m_lightType = LightType::DirectionalLight;
	m_color = Math::Vector4(1, 1, 1, 1);
	m_angle = 0;
	m_intensity = 1;
	m_influenceRange = 5;

	GetTransform().SetRotation(Math::Vector3(0.5f, -0.5f, -1.f));
}

void Light::Remove()
{
	GetContext()->GetSubsystem<Renderer>()->GetLightMap().RemoveLight(this);
}

void Light::SetLightType(Light::LightType lightType)
{
	m_lightType = lightType;
}

Light::LightType Light::GetLightType()
{
	return m_lightType;
}

void Light::SetColor(const Math::Vector4& color)
{
	m_color = color;
}

const Math::Vector4& Light::GetColor()
{
	return m_color;
}

void Light::SetIntensity(float intensity)
{
	m_intensity = intensity;
}

float Light::GetIntensity()
{
	return m_intensity;
}

void Light::SetInfluenceRange(float influenceRange)
{
	m_influenceRange = influenceRange;
}

float Light::GetInfluenceRange()
{
	return m_influenceRange;
}

void Light::SetAngle(float angle)
{
	m_angle = angle;
}

float Light::GetAngle()
{
	return m_angle;
}