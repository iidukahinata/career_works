/**
* @file    D3D12VertexBuffer.h
* @brief
*
* @date	   2022/07/22 2022年度初版
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

template<class T>
class D3D12VertexBuffer : public D3D12DeviceChild
{
public:

	bool Create(const Vector<T>& vertices) noexcept;

	void Update(const Vector<T>& vertices) noexcept;

	void IASet(UINT slot = 0) const noexcept;

	ID3D12Resource*           Get() const noexcept     { return m_buffer.Get(); };
	D3D12_VERTEX_BUFFER_VIEW& GetBufferView() noexcept { return m_bufferView; };

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;
	D3D12_VERTEX_BUFFER_VIEW m_bufferView;

	UINT m_bytesSize;
};

template<class T>
inline bool D3D12VertexBuffer<T>::Create(const Vector<T>& vertices) noexcept
{
	const UINT size = sizeof(T) * vertices.size();
	const UINT stride = sizeof(T);

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

	// バッファー生成
	HRESULT hr = GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_buffer.ReleaseAndGetAddressOf()));

	if (FAILED(hr))
	{
		return false;
	}

	// ビュー生成
	m_bufferView.BufferLocation = m_buffer->GetGPUVirtualAddress();
	m_bufferView.SizeInBytes = size;
	m_bufferView.StrideInBytes = stride;

	m_bytesSize = size;

	Update(vertices);

	return true;
}

template<class T>
inline void D3D12VertexBuffer<T>::Update(const Vector<T>& vertices) noexcept
{
	T* pData;
	HRESULT hr = m_buffer->Map(0, nullptr, reinterpret_cast<void**>(&pData));
	if (SUCCEEDED(hr)) 
	{
		memcpy_s(pData, m_bytesSize, vertices.data(), sizeof(T) * vertices.size());
		m_buffer->Unmap(0, nullptr);
	}
}

template<class T>
inline void D3D12VertexBuffer<T>::IASet(UINT slot /* = 0 */) const noexcept
{
	GetContext()->GetCommandList()->IASetVertexBuffers(slot, 1, &m_bufferView);
}