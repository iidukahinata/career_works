#include "D3D12ConstantBuffer.h"


bool D3D12ConstantBuffer::Create(UINT bufferSize, UINT count) noexcept
{
	bufferSize = AdjustToMultiples(bufferSize, 256);
	m_adjustBufferSize = bufferSize * count;

	const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_adjustBufferSize);

	auto hr = GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_constantBuffer.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_constantBufferCPU));
	ZeroMemory(m_constantBufferCPU, m_adjustBufferSize);

	return true;
}

D3D12_CONSTANT_BUFFER_VIEW_DESC D3D12ConstantBuffer::GetDesc() const noexcept
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
	desc.SizeInBytes = m_adjustBufferSize;
	return desc;
}