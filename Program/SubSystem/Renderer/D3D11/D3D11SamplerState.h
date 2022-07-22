/**
* @file    D3D11SamplerState.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include "D3D11DeviceChild.h"

class D3D11SamplerState : public D3D11DeviceChild
{
public:

	bool Create(
		D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_MODE addressU = D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_MODE addressV = D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_MODE addressW = D3D11_TEXTURE_ADDRESS_CLAMP) noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void PSSet(UINT slot = 0) const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
};