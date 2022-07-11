/**
* @file    DeferredLightMap.h
* @brief
*
* @date	   2022/07/08 2022�N�x����
*/
#pragma once


#include "../LightMap.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

#define MAX_LIGHT_COUNT 256

/**
* �N���X�^�[�h�V�F�[�f�B���O�p���C�g�Ǘ����s���B
*/
class ClusteredLightMap : public LightMap
{
	SUB_CLASS(ClusteredLightMap)
public:

	void Initialize() override;

	void Update(Camera* mainCamera) override;

	void SetAABB(const Math::Vector3& min, const Math::Vector3& max) noexcept;

private:

	void PointLightCulling(Light* light, int index) noexcept;
	void SpotLightCulling(Light* light, int index) noexcept;

	void AddPointLightToLightList(int x, int y, int z, int index) noexcept;
	void AddSpotLightToLightList(int x, int y, int z, int index) noexcept;

private:

	// * ������
	const Math::Vector3i m_cluster = Math::Vector3i(32, 8, 32);

	// * ��ԃT�C�Y
	Math::Vector3 m_aabbMax;
	Math::Vector3 m_aabbMin;

	// * �ŏ���ԃT�C�Y
	Math::Vector3 m_scale;
	Math::Vector3 m_invScale;

	struct LightList
	{
		std::vector<uint16_t> pointLightIndices;
		std::vector<uint16_t> spotLightIndices;
	};

	Vector<LightList> m_lightList;

	struct DirectionalLightDate
	{
		Math::Vector4 direction;
		Math::Vector4 color; // w intensity
	};

	struct PointLightDate
	{
		Math::Vector4 position;
		Math::Vector4 color; // w intensity
	};

	struct SpotLightDate
	{
		Math::Vector4 position;
		Math::Vector4 direction;
		Math::Vector4 color; // w intensity
	};

	struct ConstantBufferLight
	{
		Math::Vector4 eyePos;
		Math::Vector4 ambientLight;
		DirectionalLightDate directionalLight;
		Array<PointLightDate, MAX_LIGHT_COUNT> pointLights;
		Array<SpotLightDate, MAX_LIGHT_COUNT> spotLights;
	};

	D3D11ConstantBuffer<ConstantBufferLight> m_constantBuffer;

	// * Light �f�[�^�e�N�X�`��
	ID3D11Texture3D* m_texture3D;
};