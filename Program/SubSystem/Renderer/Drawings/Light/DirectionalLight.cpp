/**
* @file	   DirectionalLight.cpp
* @brief	Light”h¶ƒNƒ‰ƒX
*
* @date	   2022/04/22 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "Light.h"
#include "LightMap.h"

DirectionalLight::~DirectionalLight()
{
	if (m_lightMap)
	{
		m_lightMap->RemoveLight(this);
	}
}

void DirectionalLight::Do_Init()
{
	if (m_lightMap) 
	{
		m_lightMap->AddLight(this);
	}
}

Light::LightType DirectionalLight::GetLightType()
{
	return Light::LightType::DirectionalLight;
}

const Math::Vector4& DirectionalLight::GetDirection()
{
	return m_direction;
}

void DirectionalLight::SetDirection(const Math::Vector4& direction)
{
	m_direction = direction;
}

const Math::Vector4& DirectionalLight::GetColor()
{
	return m_color;
}

void DirectionalLight::SetColor(const Math::Vector4& color)
{
	m_color = color;
}

const float& DirectionalLight::GetIntensity()
{
	return m_intensity;
}

void DirectionalLight::SetIntensity(const float& intensity)
{
	m_intensity = intensity;
}