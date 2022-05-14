/**
* @file	   LightMap.cpp
* @brief	Light管理クラス
*
* @date	   2022/04/22 2022年度初版
* @author  飯塚陽太
*/


#include "LightMap.h"

LightMap::~LightMap()
{
	Clear();
}

void LightMap::Init()
{
	m_ambientLight = Math::Vector4(0.4f);

	m_constantBuffer.Create(sizeof(ConstantBufferLight));
}

void LightMap::Update(const Math::Vector3& cameraPos)
{
	ConstantBufferLight buffer = {};

	int pointLightCount = 0;
	int spotLightCount = 0;

	// 各Light情報を取得し、bufferにセット
	for (auto light : m_lights)
	{
		if (!light->GetEnable())
			continue;

		switch (light->GetLightType())
		{
		case Light::LightType::DirectionalLight:
			buffer.directionalLight.direction = light->GetDirection();
			buffer.directionalLight.color = light->GetColor();
			buffer.directionalLight.intensity = light->GetIntensity();
			break;

		case Light::LightType::PointLight:
			buffer.pointLights[pointLightCount].position = light->GetPosition();
			buffer.pointLights[pointLightCount].color = light->GetColor();
			buffer.pointLights[pointLightCount].intensity = light->GetIntensity();
			buffer.pointLights[pointLightCount].influenceRange = light->GetInfluenceRange();
			++pointLightCount;
			break;

		case Light::LightType::SpotLight:
			buffer.spotLights[pointLightCount].position = light->GetPosition();
			buffer.spotLights[pointLightCount].direction = light->GetDirection();
			buffer.spotLights[pointLightCount].color = light->GetColor();
			buffer.spotLights[pointLightCount].intensity = light->GetIntensity();
			buffer.spotLights[pointLightCount].influenceRange = light->GetInfluenceRange();
			buffer.spotLights[pointLightCount].angle = light->GetAngle();
			++spotLightCount;
			break;

		default:
			break;
		}
	}

	buffer.eyePos = Math::Vector4(cameraPos, 0.f);
	buffer.ambientLight = m_ambientLight;
	buffer.pointLightCount = pointLightCount;
	buffer.spotLightCount = spotLightCount;

	// GPUデータ更新
	m_constantBuffer.Update(buffer);
	
	// set buffer
	m_constantBuffer.VSSet(2);
	m_constantBuffer.PSSet(2);
}

void LightMap::Clear() noexcept
{
	m_lights.clear();
	m_lights.shrink_to_fit();
}

void LightMap::AddLight(Light* light)
{
	m_lights.push_back(light);
}

void LightMap::RemoveLight(Light* light)
{
	for (int i = 0; i < m_lights.size(); ++i)
	{
		if (m_lights[i] == light)
		{
			m_lights.erase(m_lights.begin() + i);
			break;
		}
	}
}

void LightMap::SetAmbient(const Math::Vector4& ambientLight)
{
	m_ambientLight = ambientLight;
}