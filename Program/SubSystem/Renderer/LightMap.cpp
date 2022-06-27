/**
* @file	   LightMap.cpp
* @brief   Light管理クラス
*
* @date	   2022/06/27 2022年度初版
*/


#include "LightMap.h"
#include "SubSystem/Scene/Component/Components/Light.h"

LightMap::~LightMap()
{
	Clear();
}

void LightMap::Initialize() noexcept
{
	m_ambientLight = Math::Vector4(0.5f);

	m_constantBuffer.Create(sizeof(ConstantBufferLight));
}

void LightMap::Update() noexcept
{
	ConstantBufferLight buffer = {};

	int pointLightCount = 0;
	int spotLightCount = 0;

	// 各Light情報を取得し、bufferにセット
	for (auto light : m_lights)
	{
		Math::Vector4 position(light->GetTransform().GetRotation(), 0.f);
		Math::Vector4 direction(light->GetTransform().GetRotation(), 0.f);

		switch (light->GetLightType())
		{
		case Light::LightType::DirectionalLight:
			buffer.directionalLight.direction = direction;
			buffer.directionalLight.color = light->GetColor();
			buffer.directionalLight.intensity = light->GetIntensity();
			break;

		case Light::LightType::PointLight:
			buffer.pointLights[pointLightCount].position = position;
			buffer.pointLights[pointLightCount].color = light->GetColor();
			buffer.pointLights[pointLightCount].intensity = light->GetIntensity();
			buffer.pointLights[pointLightCount].influenceRange = light->GetInfluenceRange();
			++pointLightCount;
			break;

		case Light::LightType::SpotLight:
			buffer.spotLights[pointLightCount].position = position;
			buffer.spotLights[pointLightCount].direction = direction;
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

	// 一旦決め打ち
	buffer.eyePos = Math::Vector4(0.f, 3.f, -9.f, 0);
	//buffer.eyePos = Math::Vector4(cameraPos, 0.f);

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

void LightMap::AddLight(Light* light) noexcept
{
	m_lights.push_back(light);
}

void LightMap::RemoveLight(Light* light) noexcept
{
	for (auto it = m_lights.begin(); it != m_lights.end(); it++)
	{
		if (*it == light)
		{
			m_lights.erase(it);
			break;
		}
	}
}

void LightMap::SetAmbient(const Math::Vector4& ambientLight) noexcept
{
	m_ambientLight = ambientLight;
}