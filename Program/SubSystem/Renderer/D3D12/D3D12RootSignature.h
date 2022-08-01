/**
* @file    D3D12RootSignature.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12Shader;

enum RootPramIndices
{
	PS_SRV,
	PS_UAV,
	PS_CBV,
	PS_Sampler,
	VS_SRV,
	VS_UAV,
	VS_CBV,
	VS_Sampler,
	GS_SRV,
	GS_UAV,
	GS_CBV,
	GS_Sampler,
	HS_SRV,
	HS_UAV,
	HS_CBV,
	HS_Sampler,
	DS_SRV,
	DS_UAV,
	DS_CBV,
	DS_Sampler,
	AS_Sampler,
	ALL_SRV,
	ALL_UAV,
	ALL_CBV,
	ALL_Sampler,
	MAX,
};

class D3D12RootSignature : public D3D12DeviceChild
{
public:

	bool Create(ID3DBlob* blob) noexcept;

	/** D3D12_ROOT_SIGNATURE_FLAGS�͏����ȍœK���Ƃ��ėL�� */
	bool Create(UINT parameterCount,
		class CD3DX12_ROOT_PARAMETER1* rootParameters,
		UINT sampleCount,
		D3D12_STATIC_SAMPLER_DESC* samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags) noexcept;

	/** �A�N�Z�X */
	ID3D12RootSignature* Get() const noexcept { return m_rootsignature.Get(); }
	UINT8 GetCBVRootPramIndex(ShaderType type) const noexcept;
	UINT8 GetUAVRootPramIndex(ShaderType type) const noexcept;
	UINT8 GetSRVRootPramIndex(ShaderType type) const noexcept;
	UINT8 GetSamplerRootPramIndex(ShaderType type) const noexcept;

private:

	void SetCBVRootPramIndex(ShaderType type, UINT8 index) noexcept;
	void SetUAVRootPramIndex(ShaderType type, UINT8 index) noexcept;
	void SetSRVRootPramIndex(ShaderType type, UINT8 index) noexcept;
	void SetSamplerRootPramIndex(ShaderType type, UINT8 index) noexcept;

	void InitBindSlotIndices(UINT parameterCount, class CD3DX12_ROOT_PARAMETER1* rootParameters) noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootsignature;

	// * �ePram���Ƃ�SlotIndex�l
	UINT8 m_bindSlotIndices[RootPramIndices::MAX];
};