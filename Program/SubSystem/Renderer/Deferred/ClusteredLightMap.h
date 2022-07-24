/**
* @file    DeferredLightMap.h
* @brief
*
* @date	   2022/07/13 2022�N�x����
*/
#pragma once


#include "../LightMap.h"
#include "SubSystem/Renderer/D3D11/D3D11Texture.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

#define MAX_LIGHT_COUNT 256
#define MAX_LIGHT_INDICES_COUNT 0x1000

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

		Math::Vector4 invScale;
		Math::Vector4 bias;
	};

	struct ConstantBufferLightIndeices
	{
		Array<uint16_t, MAX_LIGHT_INDICES_COUNT> lightIndices;
	};

	/* LightList����GPU�]���p�̃f�[�^�Q���쐬���܂��B*/
	ConstantBufferLight CreateConstantBufferLight(const Camera* mainCamera) noexcept;
	void UpdateLightTexture() noexcept;

	void PointLightCulling(Light* light, const uint32_t index) noexcept;
	void SpotLightCulling(Light* light, const uint32_t index) noexcept;

	void AddPointLightToLightList(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t index) noexcept;
	void AddSpotLightToLightList(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t index) noexcept;

private:

	// * ������
	static const int clusterX = 32;
	static const int clusterY = 8;
	static const int clusterZ = 32;

	// * ��ԃT�C�Y
	Math::Vector3 m_aabbMax;
	Math::Vector3 m_aabbMin;

	// * �ŏ���ԃT�C�Y
	Math::Vector3 m_scale;
	Math::Vector3 m_invScale;

	struct LightList
	{
		Vector<uint16_t> pointLightIndices;
		Vector<uint16_t> spotLightIndices;
	};

	Array<LightList, clusterX, clusterY, clusterZ> m_lightList;

	D3D11ConstantBuffer<ConstantBufferLight> m_constantBufferLight;
	D3D11ConstantBuffer<ConstantBufferLightIndeices> m_constantBufferLightIndices;

	// * Light �f�[�^�e�N�X�`��
	D3D11Texture m_texture;
};