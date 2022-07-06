/**
* @file    D3D12DescriptorHeap.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "D3D12DescriptorHeap.h"
#include "D3D12GrahicsDevice.h"

bool D3D12DescriptorHeap::Create(UINT NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC descriptHeapDesc = {};
	descriptHeapDesc.NumDescriptors = NumDescriptors;
	descriptHeapDesc.Type = type;
	descriptHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateDescriptorHeap(
		&descriptHeapDesc,
		IID_PPV_ARGS(m_descriptHeap.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		LOG_ERROR("ディスクリプタヒープの作成を失敗しました。");
		return false;
	}

	m_d12DescriptorSize = GetGraphicsDevice()->GetDevice()->GetDescriptorHandleIncrementSize(type);
	return true;
}

void D3D12DescriptorHeap::Set()
{
	GetGraphicsDevice()->GetCommandContext().GetCommandList()->SetDescriptorHeaps(1, m_descriptHeap.GetAddressOf());
}

UINT D3D12DescriptorHeap::IncrementSize()
{
	return m_d12DescriptorSize;
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart()
{
	return m_descriptHeap->GetCPUDescriptorHandleForHeapStart();
}