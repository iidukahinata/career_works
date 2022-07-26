/**
* @file    D3D12RootSignature.h
* @brief
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12RootSignature : public D3D12DeviceChild
{
public:

	/** D3D12_ROOT_SIGNATURE_FLAGSは小さな最適化として有効 */
	bool Create(UINT parameterCount,
		class CD3DX12_ROOT_PARAMETER1* rootParameters,
		UINT sampleCount,
		D3D12_STATIC_SAMPLER_DESC* samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags) noexcept;

	/** デバイス設定するための関数です。*/
	void SetGraphics() const noexcept;
	void SetCompute() const noexcept;

	ID3D12RootSignature* Get() const noexcept { return m_rootsignature.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootsignature;
};