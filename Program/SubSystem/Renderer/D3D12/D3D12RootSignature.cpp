/**
* @file    D3D12RootSignature.cpp
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/


#include <d3dcompiler.h>
#include "D3D12RootSignature.h"
#include "../directxtex/include/d3dx12.h"

bool D3D12RootSignature::Create(ID3DBlob* blob) noexcept
{
	Microsoft::WRL::ComPtr<ID3DBlob> rootSignature;
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_ROOT_SIGNATURE, 0, rootSignature.ReleaseAndGetAddressOf());
	if (FAILED(hr)) {
		//LOG_ERROR("�V�F�[�_�f�[�^���V���A�����o���܂���ł����B");
		return false;
	}

	// ���[�g�V�O�l�`���̐���
	hr = GetDevice()->CreateRootSignature(0, rootSignature->GetBufferPointer(), rootSignature->GetBufferSize(), IID_PPV_ARGS(m_rootsignature.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		//LOG_ERROR("���[�g�V�O�l�`�������Ɏ��s���܂����B");
		return false;
	}

	return true;
}

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

	// �V���A����
	Microsoft::WRL::ComPtr<ID3DBlob> rootSignature;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	HRESULT hr = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, rootSignature.GetAddressOf(), errorBlob.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// ���[�g�V�O�l�`������
	hr = GetDevice()->CreateRootSignature(
		0, rootSignature->GetBufferPointer(), rootSignature->GetBufferSize(),
		IID_PPV_ARGS(m_rootsignature.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	InitBindSlotIndices(parameterCount, rootParameters);

	return true;
}

UINT8 D3D12RootSignature::GetCBVRootPramIndex(ShaderType type) const noexcept
{
	switch (type)
	{
	case VertexShader  : return m_bindSlotIndices[VS_CBV];
	case PixelShader   : return m_bindSlotIndices[PS_CBV];
	case GeometryShader: return m_bindSlotIndices[GS_CBV];
	case HullShader	   : return m_bindSlotIndices[HS_CBV];
	case DomainShader  : return m_bindSlotIndices[DS_CBV];
	default			   : return m_bindSlotIndices[ALL_CBV];
	}
}

UINT8 D3D12RootSignature::GetSRVRootPramIndex(ShaderType type) const noexcept
{
	switch (type)
	{
	case VertexShader  : return m_bindSlotIndices[VS_SRV];
	case PixelShader   : return m_bindSlotIndices[PS_SRV];
	case GeometryShader: return m_bindSlotIndices[GS_SRV];
	case HullShader    : return m_bindSlotIndices[HS_SRV];
	case DomainShader  : return m_bindSlotIndices[DS_SRV];
	default			   : return m_bindSlotIndices[ALL_SRV];
	}
}

UINT8 D3D12RootSignature::GetUAVRootPramIndex(ShaderType type) const noexcept
{
	switch (type)
	{
	case VertexShader  : return m_bindSlotIndices[VS_UAV];
	case PixelShader   : return m_bindSlotIndices[PS_UAV];
	case GeometryShader: return m_bindSlotIndices[GS_UAV];
	case HullShader    : return m_bindSlotIndices[HS_UAV];
	case DomainShader  : return m_bindSlotIndices[DS_UAV];
	default            : return m_bindSlotIndices[ALL_UAV];
	}
}

UINT8 D3D12RootSignature::GetSamplerRootPramIndex(ShaderType type) const noexcept
{
	switch (type)
	{
	case VertexShader  : return m_bindSlotIndices[VS_Sampler];
	case PixelShader   : return m_bindSlotIndices[PS_Sampler];
	case GeometryShader: return m_bindSlotIndices[GS_Sampler];
	case HullShader    : return m_bindSlotIndices[HS_Sampler];
	case DomainShader  : return m_bindSlotIndices[DS_Sampler];
	default			   : return m_bindSlotIndices[ALL_Sampler];
	}
}

void D3D12RootSignature::SetCBVRootPramIndex(ShaderType type, UINT8 index) noexcept
{
	switch (type)
	{
	case VertexShader  : m_bindSlotIndices[VS_CBV] = index; break;
	case PixelShader   : m_bindSlotIndices[PS_CBV] = index; break;
	case GeometryShader: m_bindSlotIndices[GS_CBV] = index; break;
	case HullShader    : m_bindSlotIndices[HS_CBV] = index; break;
	case DomainShader  : m_bindSlotIndices[DS_CBV] = index; break;
	default			   : m_bindSlotIndices[ALL_CBV] = index; break;
	}
}

void D3D12RootSignature::SetUAVRootPramIndex(ShaderType type, UINT8 index) noexcept
{
	switch (type)
	{
	case VertexShader  : m_bindSlotIndices[VS_UAV] = index; break;
	case PixelShader   : m_bindSlotIndices[PS_UAV] = index; break;
	case GeometryShader: m_bindSlotIndices[GS_UAV] = index; break;
	case HullShader    : m_bindSlotIndices[HS_UAV] = index; break;
	case DomainShader  : m_bindSlotIndices[DS_UAV] = index; break;
	default			   : m_bindSlotIndices[ALL_UAV] = index; break;
	}
}

void D3D12RootSignature::SetSRVRootPramIndex(ShaderType type, UINT8 index) noexcept
{
	switch (type)
	{
	case VertexShader  : m_bindSlotIndices[VS_SRV] = index; break;
	case PixelShader   : m_bindSlotIndices[PS_SRV] = index; break;
	case GeometryShader: m_bindSlotIndices[GS_SRV] = index; break;
	case HullShader    : m_bindSlotIndices[HS_SRV] = index; break;
	case DomainShader  : m_bindSlotIndices[DS_SRV] = index; break;
	default			   : m_bindSlotIndices[ALL_SRV] = index; break;
	}
}

void D3D12RootSignature::SetSamplerRootPramIndex(ShaderType type, UINT8 index) noexcept
{
	switch (type)
	{
	case VertexShader  : m_bindSlotIndices[VS_Sampler] = index;
	case PixelShader   : m_bindSlotIndices[PS_Sampler] = index;
	case GeometryShader: m_bindSlotIndices[GS_Sampler] = index;
	case HullShader    : m_bindSlotIndices[HS_Sampler] = index;
	case DomainShader  : m_bindSlotIndices[DS_Sampler] = index;
	default			   : m_bindSlotIndices[ALL_Sampler] = index;
	}
}

void D3D12RootSignature::InitBindSlotIndices(UINT parameterCount, CD3DX12_ROOT_PARAMETER1* rootParameters) noexcept
{
	for (int i = 0; i < parameterCount; ++i)
	{
		auto param = rootParameters[i];

		// �p�����[�^�[���g�p�����ShaderStage�𒲂דƎ��f�[�^�ɕϊ�����
		auto currentShaderType = ShaderType::Max;
		switch (param.ShaderVisibility)
		{
		case D3D12_SHADER_VISIBILITY_VERTEX:
			currentShaderType = ShaderType::VertexShader;
			break;

		case D3D12_SHADER_VISIBILITY_HULL:
			currentShaderType = ShaderType::HullShader;
			break;

		case D3D12_SHADER_VISIBILITY_DOMAIN:
			currentShaderType = ShaderType::DomainShader;
			break;

		case D3D12_SHADER_VISIBILITY_GEOMETRY:
			currentShaderType = ShaderType::GeometryShader;
			break;

		case D3D12_SHADER_VISIBILITY_PIXEL:
			currentShaderType = ShaderType::PixelShader;
			break;

		case D3D12_SHADER_VISIBILITY_AMPLIFICATION:
		case D3D12_SHADER_VISIBILITY_MESH:
		case D3D12_SHADER_VISIBILITY_ALL:
			currentShaderType = ShaderType::Max;
			break;

		default: break;
		}
		
		// �p�����[�^�[�C���f�b�N�X�ɓo�^
		switch (param.DescriptorTable.pDescriptorRanges->RangeType)
		{
		case D3D12_DESCRIPTOR_RANGE_TYPE_SRV:
			SetSRVRootPramIndex(currentShaderType, i);
			break;

		case D3D12_DESCRIPTOR_RANGE_TYPE_UAV:
			SetUAVRootPramIndex(currentShaderType, i);
			break;

		case D3D12_DESCRIPTOR_RANGE_TYPE_CBV:
			SetCBVRootPramIndex(currentShaderType, i);
			break;

		case D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER:
			SetSamplerRootPramIndex(currentShaderType, i);
			break;

		default: break;
		}
	}
}