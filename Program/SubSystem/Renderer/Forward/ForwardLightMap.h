/**
* @file    ForwardLightMap.h
* @brief
*
* @date	   2022/07/13 2022�N�x����
*/
#pragma once


#include "../LightMap.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

#define MAX_LIGHT_COUNT 256

/**
* 2022/07/08�ȑO��LightMap����Ɠ������e�̏��������B
* �N���X�^�[�h�V�F�[�f�B���O�pLightMap����������܂Ŏg�p�\��B
*/
class ForwardLightMap : public LightMap
{
	SUB_CLASS(ForwardLightMap)
public:

	void Initialize() override;
	void Update(Camera* mainCamera) override;

private:

	struct DirectionalLightDate
	{
		Math::Vector4 direction;
		Math::Vector4 color; // w intensity
	};

	struct PointLightDate
	{
		Math::Vector4 position;
		Math::Vector4 color;
		float intensity;
		float influenceRange;

		Math::Vector2 padding; // 16�r�b�g�����p�ϐ�
	};

	struct SpotLightDate
	{
		Math::Vector4 position;
		Math::Vector4 direction;
		Math::Vector4 color;
		float intensity;
		float influenceRange;
		float angle;

		float padding; // 16�r�b�g�����p�ϐ�
	};

	struct ConstantBufferLight
	{
		Math::Vector4 eyePos;
		Math::Vector4 ambientLight;
		DirectionalLightDate directionalLight;
		Array<PointLightDate, MAX_LIGHT_COUNT> pointLights;
		Array<SpotLightDate, MAX_LIGHT_COUNT> spotLights;

		float pointLightCount;
		float spotLightCount;
	};

	/* LightList����GPU�]���p�f�[�^���쐬���A�߂�l�Ƃ��ĕԂ��܂��B*/
	ConstantBufferLight CreateConstantBufferLight(const Camera* mainCamera) const noexcept;

private:

	D3D11ConstantBuffer<ConstantBufferLight> m_constantBuffer;
};