/**
* @file    D3D12RootSignature.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12RootSignature : public D3D12DeviceChild
{
public:

	bool Create(D3D12_FILTER samplerFilter,
				D3D12_TEXTURE_ADDRESS_MODE samplerAdressModeU,
				D3D12_TEXTURE_ADDRESS_MODE samplerAdressModeV,
				D3D12_TEXTURE_ADDRESS_MODE samplerAdressModeW) noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void SetGraphics() const noexcept;
	void SetCompute() const noexcept;

	ID3D12RootSignature* GetRootSignature() const noexcept { return m_rootsignature.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootsignature;
};