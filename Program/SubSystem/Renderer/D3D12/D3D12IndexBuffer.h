/**
* @file    D3D12IndexBuffer.h
* @brief
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

class D3D12IndexBuffer : public D3D12DeviceChild
{
public:

	template<class T>
	bool Create(const std::vector<T>& indices, DXGI_FORMAT format) noexcept;
	bool Create(const std::vector<UINT>& indices) noexcept;
	bool Create(const std::vector<UINT16>& indices) noexcept;

	template<class T>
	void Update(const std::vector<T>& indices) noexcept;

	void IASet() const noexcept;

	ID3D12Resource*			 Get()	   const noexcept { return m_buffer.Get(); }
	D3D12_INDEX_BUFFER_VIEW& GetBufferView() noexcept { return m_bufferView; }

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;
	D3D12_INDEX_BUFFER_VIEW m_bufferView;
	UINT m_bytesSize;
};

template<class T>
FORCEINLINE bool D3D12IndexBuffer::Create(const std::vector<T>& indices, DXGI_FORMAT format) noexcept
{
	const auto bytesSize = sizeof(T) * indices.size();

	const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(bytesSize);

	// バッファー生成
	auto hr = GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_buffer.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	// ビュー生成
	m_bufferView.BufferLocation = m_buffer->GetGPUVirtualAddress();
	m_bufferView.Format = format;
	m_bufferView.SizeInBytes = bytesSize;

	m_bytesSize = bytesSize;

	Update(indices);

	return true;
}

template<class T>
FORCEINLINE void D3D12IndexBuffer::Update(const std::vector<T>& indices) noexcept
{
	UINT* pData;
	auto hr = m_buffer->Map(0, nullptr, reinterpret_cast<void**>(&pData));
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData, m_bytesSize, indices.data(), sizeof(T) * indices.size());
		m_buffer->Unmap(0, nullptr);
	}
}