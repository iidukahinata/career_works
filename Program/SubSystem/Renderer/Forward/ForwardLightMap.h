/**
* @file    ForwardLightMap.h
* @brief
*
* @date	   2022/07/08 2022年度初版
*/
#pragma once


#include "../LightMap.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

#define MAX_LIGHT_COUNT 64

/**
* 2022/07/08以前のLightMap動作と同じ内容の処理を持つ。
* クラスタードシェーディング用LightMapが完成するまで使用予定。
*/
class ForwardLightMap : public LightMap
{
	SUB_CLASS(ForwardLightMap)
public:

	void Initialize() override;
	void Update(const Math::Vector3& cameraPos) override;

private:

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
		Array<PointLightDate, MAX_LIGHT_COUNT> pointLights;
		Array<SpotLightDate, MAX_LIGHT_COUNT> spotLights;

		float pointLightCount;
		float spotLightCount;
	};

	D3D11ConstantBuffer<ConstantBufferLight> m_constantBuffer;
};