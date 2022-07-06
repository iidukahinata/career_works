/**
* @file    D3D12ConstantBuffer.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

template<class T>
class D3D12ConstantBuffer : public D3D12DeviceChild
{
public:

	bool Create(const T& buffer) noexcept;
	void Update(const T& buffer) noexcept;
	void RegisterForDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle) noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;
	HANDLE m_constantBufferCPU;
	UINT m_adjustBufferSize;
};

template<class T>
inline bool D3D12ConstantBuffer<T>::Create(const T& buffer) noexcept
{
	UINT size = sizeof(buffer);
	m_adjustBufferSize = AdjustToMultiples(size, 256);

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_adjustBufferSize);

	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_constantBuffer.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	CD3DX12_RANGE readRange(0, 0);
	m_constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_constantBufferCPU));
	memcpy_s(m_constantBufferCPU, m_adjustBufferSize, &buffer, size);

	return true;
}

template<class T>
inline void D3D12ConstantBuffer<T>::Update(const T& buffer) noexcept
{
	memcpy_s(m_constantBufferCPU, m_adjustBufferSize, &buffer, sizeof(buffer));
}

template<class T>
inline void D3D12ConstantBuffer<T>::RegisterForDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle) noexcept
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
	desc.SizeInBytes = m_adjustBufferSize;
	GetGraphicsDevice()->GetDevice()->CreateConstantBufferView(&desc, descriptorHandle);
}