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
class DeferredLightMap : public LightMap
{
	SUB_CLASS(DeferredLightMap)
public:

	void Initialize() override;
	void Update(const Math::Vector3& cameraPos) override;
};