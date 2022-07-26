/**
* @file    D3D12IndexBuffer.cpp
* @brief
*
* @date	   2022/07/26 2022îNìxèâî≈
*/


#include "D3D12IndexBuffer.h"

bool D3D12IndexBuffer::Create(const std::vector<UINT>& indices) noexcept
{
	return Create(indices, DXGI_FORMAT_R32_UINT);
}

bool D3D12IndexBuffer::Create(const std::vector<UINT16>& indices) noexcept
{
	return Create(indices, DXGI_FORMAT_R16_UINT);
}

void D3D12IndexBuffer::IASet() const noexcept
{
	GetCommandList()->IASetIndexBuffer(&m_bufferView);
}