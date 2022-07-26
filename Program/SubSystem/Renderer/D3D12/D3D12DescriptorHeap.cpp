/**
* @file    D3D12DescriptorHeap.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "D3D12DescriptorHeap.h"
#include "D3D12GrahicsDevice.h"

bool D3D12DescriptorHeap::Create(UINT NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC descriptHeapDesc = {};
	descriptHeapDesc.NumDescriptors = NumDescriptors;
	descriptHeapDesc.Type = type;
	descriptHeapDesc.NodeMask = 0;
	descriptHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	auto hr = GetDevice()->CreateDescriptorHeap(
		&descriptHeapDesc,
		IID_PPV_ARGS(m_descriptHeap.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		LOG_ERROR("ディスクリプタヒープの作成を失敗しました。");
		return false;
	}

	m_descriptorSize = GetDevice()->GetDescriptorHandleIncrementSize(type);
	return true;
}

void D3D12DescriptorHeap::Set() const noexcept
{
	ID3D12DescriptorHeap* descriptHeaps[] = { m_descriptHeap.Get() };
	GetCommandList()->SetDescriptorHeaps(1, descriptHeaps);
}

void D3D12DescriptorHeap::SetGraphicsRootTable(UINT pramatorIndex) const noexcept
{
	GetCommandList()->SetGraphicsRootDescriptorTable(pramatorIndex, m_descriptHeap->GetGPUDescriptorHandleForHeapStart());
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart() noexcept
{
	return m_descriptHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetGPUDescriptorHandleForHeapStart() noexcept
{
	return m_descriptHeap->GetGPUDescriptorHandleForHeapStart();
}