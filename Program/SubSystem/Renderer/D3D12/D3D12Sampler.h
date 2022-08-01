/**
* @file    D3D12Sampler.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12DescriptorAllocator.h"

class D3D12Sampler : public D3D12DeviceChild
{
public:

	~D3D12Sampler();

	void Create(const D3D12_SAMPLER_DESC& desc) noexcept;
	void Create(
		D3D12_FILTER filter = D3D12_FILTER_ANISOTROPIC,
		D3D12_TEXTURE_ADDRESS_MODE addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP) noexcept;

	void VSSet(UINT slot = 0) noexcept;
	void PSSet(UINT slot = 0) noexcept;
	void GSSet(UINT slot = 0) noexcept;

	/** �A�N�Z�X */
	UINT						GetID()		   const noexcept { return m_id; }
	D3D12_SAMPLER_DESC			GetDesc()	   const noexcept { return m_samplerDesc; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle() const noexcept { return m_descriptor->m_cpuHandle; }

private:

	// * �������ݒ肩��쐬����� SampelrMap ��� ID
	UINT m_id = 0;

	D3D12_SAMPLER_DESC m_samplerDesc;

	D3D12Descriptor* m_descriptor = nullptr;
};