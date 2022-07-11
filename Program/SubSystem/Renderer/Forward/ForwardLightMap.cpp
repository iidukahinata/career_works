/**
* @file    ForwardLightMap.cpp
* @brief
*
* @date	   2022/07/08 2022年度初版
*/


#include "ForwardLightMap.h"
#include "SubSystem/Scene/Component/Components/Light.h"
#include "SubSystem/Scene/Component/Components/Camera.h"

void ForwardLightMap::Initialize()
{
	m_ambientLight = Math::Vector4(0.5f);

	m_constantBuffer.Create(sizeof(ConstantBufferLight));
}

void ForwardLightMap::Update(Camera* mainCamera)
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
		case LightType::DirectionalLight:
			buffer.directionalLight.direction = direction;
			buffer.directionalLight.color = light->GetColor();
			buffer.directionalLight.intensity = light->GetIntensity();
			break;

		case LightType::PointLight:
			buffer.pointLights[pointLightCount].position = position;
			buffer.pointLights[pointLightCount].color = light->GetColor();
			buffer.pointLights[pointLightCount].intensity = light->GetIntensity();
			buffer.pointLights[pointLightCount].influenceRange = light->GetInfluenceRange();
			++pointLightCount;
			break;

		case LightType::SpotLight:
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

	buffer.eyePos = Math::Vector4(mainCamera->GetTransform().GetPosition(), 0);
	buffer.ambientLight = m_ambientLight;
	buffer.pointLightCount = pointLightCount;
	buffer.spotLightCount = spotLightCount;

	// GPUデータ更新
	m_constantBuffer.Update(buffer);

	// set buffer
	m_constantBuffer.VSSet(2);
	m_constantBuffer.PSSet(2);
}