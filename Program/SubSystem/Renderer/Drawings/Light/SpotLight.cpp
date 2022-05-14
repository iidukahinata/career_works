/**
* @file	   SpotLight.cpp
* @brief	Light”h¶ƒNƒ‰ƒX
*
* @date	   2022/04/22 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "Light.h"
#include "LightMap.h"

SpotLight::~SpotLight()
{
	if (m_lightMap)
	{
		m_lightMap->RemoveLight(this);
	}
}

void SpotLight::Do_Init()
{
	if (m_lightMap) 
	{
		m_lightMap->AddLight(this);
	}
}

Light::LightType SpotLight::GetLightType()
{
	return Light::LightType::SpotLight;
}

const Math::Vector4& SpotLight::GetPosition()
{
	return m_position;
}

void SpotLight::SetPosition(const Math::Vector4& position)
{
	m_position = position;
}

const Math::Vector4& SpotLight::GetDirection()
{
	return m_direction;
}

void SpotLight::SetDirection(const Math::Vector4& direction)
{
	m_direction = direction;
}

const Math::Vector4& SpotLight::GetColor()
{
	return m_color;
}

void SpotLight::SetColor(const Math::Vector4& color)
{
	m_color = color;
}

const float& SpotLight::GetInfluenceRange()
{
	return m_influenceRange;
}

void SpotLight::SetInfluenceRange(const float& influenceRange)
{
	m_influenceRange = influenceRange;
}

const float& SpotLight::GetAngle()
{
	return m_angle;
}

void SpotLight::SetAngle(const float& angle)
{
	m_angle = angle;
}

const float& SpotLight::GetIntensity()
{
	return m_intensity;
}

void SpotLight::SetIntensity(const float& intensity)
{
	m_intensity = intensity;
}
