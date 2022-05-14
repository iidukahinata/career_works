/**
* @file    D3D11IndexBuffer.cpp
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
*/


#include "D3D11IndexBuffer.h"
#include "SubSystem/Log/DebugLog.h"

bool D3D11IndexBuffer::Create(const std::vector<UINT>& indices, D3D11_USAGE usage /* = D3D11_USAGE_DEFAULT */) noexcept
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = (usage & D3D11_USAGE_DYNAMIC) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = (usage & D3D11_USAGE_DYNAMIC) ? D3D11_CPU_ACCESS_WRITE : 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indices.data();

	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateBuffer(&bufferDesc, &InitData, m_indexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		LOG_ERROR("インデックスバッファー作成失敗 : D3D11IndexBuffer.h");
		return false;
	}
	return true;
}

void D3D11IndexBuffer::Update(const std::vector<UINT>& indices) noexcept
{
	auto context = GetGraphicsDevice()->GetContext();

	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = context->Map(m_indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData.pData, pData.RowPitch, indices.data(), sizeof(UINT) * indices.size());
		context->Unmap(m_indexBuffer.Get(), 0);
	}
}

void D3D11IndexBuffer::IASet() noexcept
{
	GetGraphicsDevice()->GetContext()->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}