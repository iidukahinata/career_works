/**
* @file    D3D12IndexBuffer.h
* @brief
*
* @date	   2022/08/01 2022年度初版
*/
#pragma once


#include "D3D12Buffer.h"
#include "../directxtex/include/d3dx12.h"

class D3D12IndexBuffer : public D3D12Buffer
{
public:

	bool Create(const std::vector<UINT>& indices) noexcept;
	bool Create(const std::vector<UINT16>& indices) noexcept;

	template<class T>
	void Update(const std::vector<T>& indices) noexcept;

	void IASet() noexcept;

	/** アクセス */
	D3D12_INDEX_BUFFER_VIEW& GetBufferView() noexcept { return m_bufferView; }

private:

	template<class T>
	bool Create(const std::vector<T>& indices, DXGI_FORMAT format) noexcept;

private:

	D3D12_INDEX_BUFFER_VIEW m_bufferView;

	UINT m_bytesSize;
};

template<class T>
FORCEINLINE bool D3D12IndexBuffer::Create(const std::vector<T>& indices, DXGI_FORMAT format) noexcept
{
	UINT bytesSize = sizeof(T) * indices.size();

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(bytesSize);

	auto ret = D3D12Buffer::Create(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc);
	if (!ret) {
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
	UpdateBuffer(m_bytesSize, const_cast<T*>(indices.data()), sizeof(T) * indices.size());
}