/**
* @file    D3D12IndexBuffer.cpp
* @brief
*
* @date	   2022/05/13 2022年度初版
* @author  飯塚陽太
*/


#include "D3D12IndexBuffer.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12IndexBuffer::Create(const std::vector<UINT>& indices) noexcept
{
	UINT bytesSize = sizeof(UINT) * indices.size();

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(bytesSize);

	// バッファー生成
	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateCommittedResource(
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
	m_bufferView.Format = DXGI_FORMAT_R32_UINT;
	m_bufferView.SizeInBytes = bytesSize;

	m_bytesSize = bytesSize;

	return true;
}

void D3D12IndexBuffer::Update(const std::vector<UINT>& indices) noexcept
{
	UINT* pData;
	HRESULT hr = m_buffer->Map(0, nullptr, reinterpret_cast<void**>(&pData));
	if (SUCCEEDED(hr)) 
	{
		memcpy_s(pData, m_bytesSize, indices.data(), sizeof(UINT) * indices.size());
		m_buffer->Unmap(0, nullptr);
	}
}

void D3D12IndexBuffer::IASet() noexcept
{
	GetGraphicsDevice()->GetCommandContext().GetCommandList()->IASetIndexBuffer(&m_bufferView);
}