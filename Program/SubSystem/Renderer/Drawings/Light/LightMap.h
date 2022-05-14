/**
* @file	   LightMap.h
* @brief	Light管理クラス
*
* @date	   2022/04/22 2022年度初版
* @author  飯塚陽太
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

	// * Sceneにセットされている全てのLightオブジェクト
	std::vector<Light*> m_lights;

	// * 環境光カラー
	Math::Vector4 m_ambientLight;

	struct DirectionalLightDate
	{
		Math::Vector4 direction;
		Math::Vector4 color;
		float intensity;

		Math::Vector3 padding; // 16ビット調整用変数
	};

	struct PointLightDate
	{
		Math::Vector4 position;
		Math::Vector4 color;
		float intensity;
		float influenceRange;

		Math::Vector2 padding; // 16ビット調整用変数
	};

	struct SpotLightDate
	{
		Math::Vector4 position;
		Math::Vector4 direction;
		Math::Vector4 color;
		float intensity;
		float influenceRange;
		float angle;

		float padding; // 16ビット調整用変数
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