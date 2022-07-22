/**
* @file    D3D12RootSignature.cpp
* @brief
*
* @date	   2022/07/22 2022年度初版
*/


#include "D3D12RootSignature.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12RootSignature::Create(
	D3D12_FILTER samplerFilter,
	D3D12_TEXTURE_ADDRESS_MODE samplerAdressModeU,
	D3D12_TEXTURE_ADDRESS_MODE samplerAdressModeV,
	D3D12_TEXTURE_ADDRESS_MODE samplerAdressModeW
) noexcept
{
	D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
	ZeroMemory(&samplerDesc, sizeof(D3D12_STATIC_SAMPLER_DESC));
	samplerDesc.Filter = samplerFilter;
	samplerDesc.AddressU = samplerAdressModeU;
	samplerDesc.AddressV = samplerAdressModeV;
	samplerDesc.AddressW = samplerAdressModeW;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	// パラメータ設定
	CD3DX12_DESCRIPTOR_RANGE1 ranges[3] = {};
	CD3DX12_ROOT_PARAMETER1 rootParameters[3] = {};

	//===定数バッファ用設定=====================================
	ranges[0].Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 8,
		0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC,
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND);

	rootParameters[0].InitAsDescriptorTable(1, &ranges[0]);
	//==========================================================

	//===テクスチャ用設定=======================================
	ranges[1].Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 32,
		0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC,
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND);

	rootParameters[1].InitAsDescriptorTable(1, &ranges[1]);
	//==========================================================

	//===順序なしアクセスビュー用設定===========================
	ranges[2].Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 8,
		0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC,
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND);

	rootParameters[2].InitAsDescriptorTable(1, &ranges[2]);
	//==========================================================

	// 小さな最適化として、アクセス拒否のフラグを指定する
	// ピクセルシェーダーからのアクセスは受け付ける
	D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;

	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_1(_countof(rootParameters), rootParameters, 1, &samplerDesc, rootSignatureFlags);

	// シリアル化
	Microsoft::WRL::ComPtr<ID3DBlob> rootSignature;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	HRESULT hr = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, rootSignature.GetAddressOf(), errorBlob.GetAddressOf());
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

void D3D12RootSignature::SetGraphics()
{
	GetContext()->GetCommandList()->SetGraphicsRootSignature(m_rootsignature.Get());
}

void D3D12RootSignature::SetCompute()
{
	GetContext()->GetCommandList()->SetComputeRootSignature(m_rootsignature.Get());
}