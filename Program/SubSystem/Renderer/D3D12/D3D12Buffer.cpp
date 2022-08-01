/**
* @file    D3D12Buffer.cpp
* @brief
*
* @date	   2022/07/29 2022”N“x‰”Å
*/


#include "D3D12Buffer.h"

bool D3D12Buffer::Create(
	const D3D12_HEAP_PROPERTIES* heapProperties,
	D3D12_HEAP_FLAGS heapFlags,
	const D3D12_RESOURCE_DESC* desc,
	D3D12_RESOURCE_STATES initialResourceState /* = D3D12_RESOURCE_STATE_GENERIC_READ */,
	const D3D12_CLEAR_VALUE* optimizedClearValue /* = nullptr */
) noexcept
{
	HRESULT hr = GetDevice()->CreateCommittedResource(
		heapProperties,
		heapFlags,
		desc,
		initialResourceState,
		optimizedClearValue,
		IID_PPV_ARGS(m_buffer.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	return true;
}

void D3D12Buffer::UpdateBuffer(UINT destSize, void* srcPtr, UINT srcSize) noexcept
{
	void* pData;
	HRESULT hr = m_buffer->Map(0, nullptr, reinterpret_cast<void**>(&pData));
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData, destSize, srcPtr, srcSize);
		m_buffer->Unmap(0, nullptr);
	}
}