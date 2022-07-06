/**
* @file    D3D12DescriptorHeap.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12DescriptorHeap : public D3D12DeviceChild
{
public:

	bool Create(UINT NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void Set();

	UINT IncrementSize();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart();

private:

	UINT m_d12DescriptorSize;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptHeap;
};