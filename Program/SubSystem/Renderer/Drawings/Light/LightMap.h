/**
* @file	   LightMap.h
* @brief	Light�Ǘ��N���X
*
* @date	   2022/04/22 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "Light.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

#define MAX_LIGHT_COUNT 64

class LightMap
{
public:

	~LightMap();

	void Init();
	void Update(const Math::Vector3& eyePos);
	void Clear() noexcept;

	void AddLight(Light* light);
	void RemoveLight(Light* light);

	void SetAmbient(const Math::Vector4& ambient);

private:

	// * Scene�ɃZ�b�g����Ă���S�Ă�Light�I�u�W�F�N�g
	std::vector<Light*> m_lights;

	// * �����J���[
	Math::Vector4 m_ambientLight;

	struct DirectionalLightDate
	{
		Math::Vector4 direction;
		Math::Vector4 color;
		float intensity;

		Math::Vector3 padding; // 16�r�b�g�����p�ϐ�
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
		PointLightDate pointLights[MAX_LIGHT_COUNT];
		SpotLightDate spotLights[MAX_LIGHT_COUNT];

		float pointLightCount;
		float spotLightCount;
	};

	D3D11ConstantBuffer<ConstantBufferLight> m_constantBuffer;
};