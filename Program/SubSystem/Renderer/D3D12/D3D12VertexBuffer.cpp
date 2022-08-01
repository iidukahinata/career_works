/**
* @file    D3D12VertexBuffer.cpp
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/


#include "D3D12VertexBuffer.h"
#include "D3D12CommandContext.h"
#include "../directxtex/include/d3dx12.h"

bool D3D12VertexBuffer::Create(UINT size, UINT stride) noexcept
{
	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

	auto ret = D3D12Buffer::Create(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc);
	if (!ret) {
		return false;
	}

	// �r���[����
	m_bufferView.BufferLocation = m_buffer->GetGPUVirtualAddress();
	m_bufferView.SizeInBytes = size;
	m_bufferView.StrideInBytes = stride;

	return true;
}

void D3D12VertexBuffer::IASet(UINT slot /* = 0 */) noexcept
{
	GetCommandContext()->SetVertexBuffer(&m_bufferView);
}