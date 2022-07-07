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
class DeferredLightMap : public LightMap
{
	SUB_CLASS(DeferredLightMap)
public:

	void Initialize() override;
	void Update(const Math::Vector3& cameraPos) override;
};