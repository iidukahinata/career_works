/**
* @file    D3D12Texture.cpp
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/


#include "D3D12Texture.h"
#include "D3D12GrahicsDevice.h"

bool D3D12Texture::Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta)
{
	auto hr = DirectX::CreateTextureEx(
		GetGraphicsDevice()->GetDevice(), meta,
		D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE, false,
		m_texture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("ShaderResourceView ÇÃê∂ê¨Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
		return false;
	}
	return true;
}

void D3D12Texture::SetResource(ID3D12Resource* resource)
{
	m_texture = resource;
}

ID3D12Resource* D3D12Texture::GetResource() const noexcept
{
	return m_texture.Get();
}

ID3D12Resource** D3D12Texture::GetAddressOfResource() noexcept
{
	return m_texture.GetAddressOf();
}