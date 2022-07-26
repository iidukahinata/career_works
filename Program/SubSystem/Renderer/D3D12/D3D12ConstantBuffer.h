/**
* @file    D3D12ConstantBuffer.h
* @brief
*
* @date	   2022/07/26 2022îNìxèâî≈
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

template<class T>
class D3D12ConstantBuffer : public D3D12DeviceChild
{
public:

	bool Create(const T& buffer = T(), UINT count = 1) noexcept;
	void Update(const T& buffer) noexcept;
	void RegisterForDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle) noexcept;

	template<class U = T*>
	U GetCPUData() const noexcept;
	ID3D12Resource* Get() const noexcept { return m_constantBuffer.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;
	HANDLE m_constantBufferCPU;
	UINT m_adjustBufferSize;
};

template<class T>
FORCEINLINE bool D3D12ConstantBuffer<T>::Create(const T& buffer /* = T()*/, UINT count /* = 1 */) noexcept
{
	auto size = sizeof(buffer);
	size = AdjustToMultiples(size, 256);
	m_adjustBufferSize = size * count;

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

template<class T>
FORCEINLINE void D3D12ConstantBuffer<T>::Update(const T& buffer) noexcept
{
	memcpy_s(m_constantBufferCPU, m_adjustBufferSize, &buffer, sizeof(buffer));
}

template<class T>
FORCEINLINE void D3D12ConstantBuffer<T>::RegisterForDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle) noexcept
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
	desc.SizeInBytes = m_adjustBufferSize;
	GetDevice()->CreateConstantBufferView(&desc, descriptorHandle);
}

template<class T> template<class U /* = T* */>
FORCEINLINE U D3D12ConstantBuffer<T>::GetCPUData() const noexcept
{
	return static_cast<U>(m_constantBufferCPU);
}