/**
* @file    DeferredLightMap.h
* @brief
*
* @date	   2022/07/08 2022年度初版
*/
#pragma once


#include "../LightMap.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

/**
* クラスタードシェーディング用ライト管理を行う。
*/
class ClusteredLightMap : public LightMap
{
	SUB_CLASS(ClusteredLightMap)
public:

	void Initialize() override;

	void Update(Camera* mainCamera) override;

	void SetAABB(const Math::Vector3& min, const Math::Vector3& max);

private:

	struct LightStruct
	{
		uint32_t offset;
		uint32_t lightCount;
	};

	// * 分割数
	const Math::Vector3i m_cluster = Math::Vector3i(32, 8, 32);

	// * 空間サイズ
	Math::Vector3 m_aabbMax;
	Math::Vector3 m_aabbMin;

	// * 最小空間サイズ
	Math::Vector3 m_scale;
	Math::Vector3 m_invScale;

	// * Light データテクスチャ
	ID3D11Texture3D* m_texture3D;
};