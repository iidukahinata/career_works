/**
* @file    DeferredLightMap.h
* @brief
*
* @date	   2022/07/08 2022�N�x����
*/
#pragma once


#include "../LightMap.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

/**
* �N���X�^�[�h�V�F�[�f�B���O�p���C�g�Ǘ����s���B
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

	// * ������
	const Math::Vector3i m_cluster = Math::Vector3i(32, 8, 32);

	// * ��ԃT�C�Y
	Math::Vector3 m_aabbMax;
	Math::Vector3 m_aabbMin;

	// * �ŏ���ԃT�C�Y
	Math::Vector3 m_scale;
	Math::Vector3 m_invScale;

	// * Light �f�[�^�e�N�X�`��
	ID3D11Texture3D* m_texture3D;
};