/**
* @file	   PointLight.cpp
* @brief	Light”h¶ƒNƒ‰ƒX
*
* @date	   2022/04/22 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "Light.h"
#include "LightMap.h"

PointLight::~PointLight()
{
	if (m_lightMap)
	{
		m_lightMap->RemoveLight(this);
	}
}

void PointLight::Do_Init()
{
	if (m_lightMap) 
	{
		m_lightMap->AddLight(this);
	}
}

Light::LightType PointLight::GetLightType()
{
	return Light::LightType::PointLight;
}

const Math::Vector4& PointLight::GetPosition()
{
	return m_position;
}

void PointLight::SetPosition(const Math::Vector4& position)
{
	m_position = position;
}

const Math::Vector4& PointLight::GetColor()
{
	return m_color;
}

void PointLight::SetColor(const Math::Vector4& color)
{
	m_color = color;
}

const float& PointLight::GetInfluenceRange()
{
	return m_influenceRange;
}

void PointLight::SetInfluenceRange(const float& influenceRange)
{
	m_influenceRange = influenceRange;
}

const float& PointLight::GetIntensity()
{
	return m_intensity;
}

void PointLight::SetIntensity(const float& intensity)
{
	m_intensity = intensity;
}