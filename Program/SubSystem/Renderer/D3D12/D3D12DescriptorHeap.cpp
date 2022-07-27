/**
* @file    D3D12DescriptorHeap.cpp
* @brief
*
* @date	   2022/07/27 2022年度初版
*/


#include "D3D12DescriptorHeap.h"
#include "D3D12GrahicsDevice.h"
#include "D3D12Texture.h"
#include "D3D12ConstantBuffer.h"

bool D3D12DescriptorHeap::Create(UINT NumDescriptors, DESCRIPTOR_HEAP_TYPE type) noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC descriptHeapDesc = {};
	descriptHeapDesc.NumDescriptors = NumDescriptors;
	descriptHeapDesc.Type = static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(type);
	descriptHeapDesc.NodeMask = 0;
	descriptHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	auto hr = GetDevice()->CreateDescriptorHeap(
		&descriptHeapDesc,
		IID_PPV_ARGS(m_descriptHeap.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		LOG_ERROR("ディスクリプタヒープの作成を失敗しました。");
		return false;
	}

	m_descriptorSize = GetDevice()->GetDescriptorHandleIncrementSize(static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(type));
	m_heapType = type;

	return true;
}

void D3D12DescriptorHeap::RegisterSampler(D3D12_SAMPLER_DESC samplerDesc) noexcept
{
	ASSERT(m_descriptHeap);
	ASSERT(m_heapType == DESCRIPTOR_HEAP_TYPE_SAMPLER);

	GetDevice()->CreateSampler(&samplerDesc, m_descriptHeap->GetCPUDescriptorHandleForHeapStart());
}

void D3D12DescriptorHeap::RegisterConstantBufferView(D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc) noexcept
{
	ASSERT(m_descriptHeap);
	ASSERT(m_heapType == DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	GetDevice()->CreateConstantBufferView(&cbvDesc, m_descriptHeap->GetCPUDescriptorHandleForHeapStart());
}

void D3D12DescriptorHeap::RegisterUnorderedAccessView(ID3D12Resource* resource, D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc) noexcept
{
	ASSERT(m_descriptHeap);
	ASSERT(m_heapType == DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	GetDevice()->CreateUnorderedAccessView(resource, nullptr, &uavDesc, m_descriptHeap->GetCPUDescriptorHandleForHeapStart());
}

void D3D12DescriptorHeap::RegisterShaderResourceView(ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc) noexcept
{
	ASSERT(m_descriptHeap);
	ASSERT(m_heapType == DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	GetDevice()->CreateShaderResourceView(resource, &srvDesc, m_descriptHeap->GetCPUDescriptorHandleForHeapStart());
}

void D3D12DescriptorHeap::Set() const noexcept
{
	ASSERT(m_descriptHeap);

	ID3D12DescriptorHeap* descriptHeaps[] = { m_descriptHeap.Get() };
	GetCommandList()->SetDescriptorHeaps(1, descriptHeaps);
}

void D3D12DescriptorHeap::SetGraphicsRootTable(UINT pramatorIndex) const noexcept
{
	ASSERT(m_descriptHeap);

	GetCommandList()->SetGraphicsRootDescriptorTable(pramatorIndex, m_descriptHeap->GetGPUDescriptorHandleForHeapStart());
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart() noexcept
{
	ASSERT(m_descriptHeap);

	return m_descriptHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetGPUDescriptorHandleForHeapStart() noexcept
{
	ASSERT(m_descriptHeap);

	return m_descriptHeap->GetGPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapEnd() noexcept
{
	ASSERT(m_descriptHeap);

	auto handle = m_descriptHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += (GetIncrementSize() * m_registerResourceCount);
	return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetGPUDescriptorHandleForHeapEnd() noexcept
{
	ASSERT(m_descriptHeap);

	auto handle = m_descriptHeap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += (GetIncrementSize() * m_registerResourceCount);
	return handle;
}