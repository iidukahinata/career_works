/**
* @file    D3D12ConstantBuffer.cpp
* @brief
*
* @date	   2022/08/01 2022”N“x‰”Å
*/


#include "D3D12ConstantBuffer.h"
#include "D3D12GrahicsDevice.h"
#include "../directxtex/include/d3dx12.h"

bool D3D12ConstantBuffer::Create(UINT bufferSize) noexcept
{
	bufferSize = (bufferSize + 0xff) & ~0xff;
	const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	auto ret = D3D12Buffer::Create(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc);
	if (!ret) {
		return false;
	}

	m_view.Create(m_buffer->GetGPUVirtualAddress(), bufferSize);

	m_buffer->Map(0, nullptr, &m_constantBufferCPU);
	ZeroMemory(m_constantBufferCPU, m_view.GetDesc().SizeInBytes);

	return true;
}

void D3D12ConstantBuffer::VSSet(UINT slot /* = 0 */) noexcept
{
	GetCommandContext()->SetConstantBuffer(ShaderType::VertexShader, slot, &m_view);
}

void D3D12ConstantBuffer::PSSet(UINT slot /* = 0 */) noexcept
{
	GetCommandContext()->SetConstantBuffer(ShaderType::PixelShader, slot, &m_view);
}

void D3D12ConstantBuffer::GSSet(UINT slot /* = 0 */) noexcept
{
	GetCommandContext()->SetConstantBuffer(ShaderType::GeometryShader, slot, &m_view);
}