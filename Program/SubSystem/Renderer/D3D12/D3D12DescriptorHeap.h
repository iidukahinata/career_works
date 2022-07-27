/**
* @file    D3D12DescriptorHeap.h
* @brief
*
* @date	   2022/07/27 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

enum DESCRIPTOR_HEAP_TYPE
{
	DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
	DESCRIPTOR_HEAP_TYPE_SAMPLER,
	DESCRIPTOR_HEAP_TYPE_RTV,
	DESCRIPTOR_HEAP_TYPE_DSV,
	DESCRIPTOR_HEAP_TYPE_NUM_TYPES,
};

class D3D12DescriptorHeap : public D3D12DeviceChild
{
public:

	bool Create(UINT NumDescriptors, DESCRIPTOR_HEAP_TYPE type) noexcept;

	/** register method */
	void RegisterSampler(D3D12_SAMPLER_DESC samplerDesc) noexcept;
	void RegisterConstantBufferView(D3D12_CONSTANT_BUFFER_VIEW_DESC constantDesc) noexcept;
	void RegisterUnorderedAccessView(ID3D12Resource* resource, D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc) noexcept;
	void RegisterShaderResourceView(ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc) noexcept;

	/** デバイス設定するための関数です。*/
	void Set() const noexcept;
	void SetGraphicsRootTable(UINT pramatorIndex) const noexcept;

	/** access method */
	UINT GetIncrementSize() const noexcept { return m_descriptorSize; }
	ID3D12DescriptorHeap* Get() const noexcept { return m_descriptHeap.Get(); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart() noexcept;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapStart() noexcept;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapEnd() noexcept;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapEnd() noexcept;

private:

	UINT m_descriptorSize;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptHeap;

	UINT m_registerResourceCount = 0;
	DESCRIPTOR_HEAP_TYPE m_heapType;
};