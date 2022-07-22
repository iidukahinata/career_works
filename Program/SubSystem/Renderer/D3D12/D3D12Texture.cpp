/**
* @file    D3D12Texture.cpp
* @brief
*
* @date	   2022/07/22 2022年度初版
*/


#include "D3D12Texture.h"
#include "D3D12GrahicsDevice.h"

bool D3D12Texture::Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta)
{
	auto hr = DirectX::CreateTexture(GetDevice(), meta, m_texture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("ShaderResourceView の生成に失敗しました。");
		return false;
	}
	return true;
}

void D3D12Texture::SetResource(ID3D12Resource* resource)
{
	m_texture = resource;
}