/**
* @file    D3D12RootSignature.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "D3D12RootSignature.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12RootSignature::Create(
	UINT parameterCount,
	CD3DX12_ROOT_PARAMETER1* rootParameters,
	UINT sampleCount,
	D3D12_STATIC_SAMPLER_DESC* samplerDesc,
	D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags
) noexcept
{
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_1(parameterCount, rootParameters, sampleCount, samplerDesc, rootSignatureFlags);

	// シリアル化
	Microsoft::WRL::ComPtr<ID3DBlob> rootSignature;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	auto hr = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, rootSignature.GetAddressOf(), errorBlob.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// ルートシグネチャ生成
	hr = GetDevice()->CreateRootSignature(
		0, rootSignature->GetBufferPointer(), rootSignature->GetBufferSize(),
		IID_PPV_ARGS(m_rootsignature.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}
	return true;
}

void D3D12RootSignature::SetGraphics() const noexcept
{
	GetCommandList()->SetGraphicsRootSignature(m_rootsignature.Get());
}

void D3D12RootSignature::SetCompute() const noexcept
{
	GetCommandList()->SetComputeRootSignature(m_rootsignature.Get());
}