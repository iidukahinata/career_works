/**
* @file    D3D12DescriptorHeap.h
* @brief
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12DescriptorHeap : public D3D12DeviceChild
{
public:

	bool Create(UINT NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

	/** デバイス設定するための関数です。*/
	void Set() const noexcept;
	void SetGraphicsRootTable(UINT pramatorIndex) const noexcept;

	UINT GetIncrementSize() const noexcept { return m_descriptorSize; }
	ID3D12DescriptorHeap* Get() const noexcept { return m_descriptHeap.Get(); }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart() noexcept;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapStart() noexcept;

private:

	UINT m_descriptorSize;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptHeap;
};