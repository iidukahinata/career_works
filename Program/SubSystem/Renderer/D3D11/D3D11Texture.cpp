/**
* @file    D3D11Texture.cpp
* @brief
*
* @date	   2022/05/11 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "D3D11Texture.h"
#include "SubSystem/Log/DebugLog.h"

bool D3D11Texture::Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta)
{
	auto hr = DirectX::CreateShaderResourceViewEx(
		GetGraphicsDevice()->GetDevice(),
		images, imageSize, meta,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false,
		m_shaderResourceView.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("ShaderResourceView ‚Ì¶¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
		return false;
	}
	return true;
}

void D3D11Texture::Bind(UINT slot /* = 0 */)
{
	GetGraphicsDevice()->GetContext()->PSSetShaderResources(slot, 1, m_shaderResourceView.GetAddressOf());
}

void D3D11Texture::SetShaderResourceView(ID3D11ShaderResourceView* shaderResourceView) noexcept
{
	m_shaderResourceView = shaderResourceView;
}

ID3D11ShaderResourceView* D3D11Texture::GetShaderResourceView() const noexcept
{
	return m_shaderResourceView.Get();
}

ID3D11ShaderResourceView** D3D11Texture::GetAddressOfShaderResourceView() noexcept
{
	return m_shaderResourceView.GetAddressOf();
}