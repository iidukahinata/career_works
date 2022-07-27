/**
* @file    ForwardLightMap.cpp
* @brief
*
* @date	   2022/07/27 2022年度初版
*/


#include "ForwardLightMap.h"
#include "SubSystem/Scene/Component/Components/Light.h"
#include "SubSystem/Scene/Component/Components/Camera.h"

void ForwardLightMap::Initialize()
{
	m_ambientLight = Math::Vector4(0.5f);

	m_descriptHeap.Create(1, DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_constantBuffer.Create(sizeof(ConstantBufferLight));
	m_descriptHeap.RegisterConstantBufferView(m_constantBuffer.GetDesc());
}

void ForwardLightMap::Update(Camera* mainCamera)
{
	// pre update
	ConstantBufferLight buffer = CreateConstantBufferLight(mainCamera);

	// update buffer
	m_constantBuffer.Update(buffer);
}

ForwardLightMap::ConstantBufferLight ForwardLightMap::CreateConstantBufferLight(const Camera* mainCamera) const noexcept
{
	ConstantBufferLight buffer = {};

	int pointLightCount = 0;
	int spotLightCount = 0;

	// 各Light情報を取得し、bufferにセット
	for (auto light : m_lights)
	{
		switch (light->GetLightType())
		{
		case LightType::DirectionalLight:
			buffer.directionalLight.direction = Math::Vector4(light->GetTransform().GetRotation(), 0.f);
			buffer.directionalLight.color = light->GetColor();
			buffer.directionalLight.color.w = light->GetIntensity();
			break;

		case LightType::PointLight:
			buffer.pointLights[pointLightCount].position = Math::Vector4(light->GetTransform().GetPosition(), 0.f);
			buffer.pointLights[pointLightCount].color = light->GetColor();
			buffer.pointLights[pointLightCount].intensity = light->GetIntensity();
			buffer.pointLights[pointLightCount].influenceRange = light->GetInfluenceRange();
			++pointLightCount;
			break;

		case LightType::SpotLight:
			buffer.spotLights[spotLightCount].position = Math::Vector4(light->GetTransform().GetPosition(), 0.f);
			buffer.spotLights[spotLightCount].direction = Math::Vector4(light->GetTransform().GetRotation(), 0.f);
			buffer.spotLights[spotLightCount].color = light->GetColor();
			buffer.spotLights[spotLightCount].intensity = light->GetIntensity();
			buffer.spotLights[spotLightCount].influenceRange = light->GetInfluenceRange();
			buffer.spotLights[spotLightCount].angle = light->GetAngle();
			++spotLightCount;
			break;

		default:
			break;
		}
	}
	
	// 他Lightデータを設定
	buffer.eyePos = Math::Vector4(mainCamera->GetTransform().GetPosition(), 0);
	buffer.ambientLight = m_ambientLight;
	buffer.pointLightCount = pointLightCount;
	buffer.spotLightCount = spotLightCount;

	return buffer;
}