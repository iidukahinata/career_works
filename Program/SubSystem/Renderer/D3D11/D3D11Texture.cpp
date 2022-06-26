/**
* @file    D3D11Texture.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "D3D11Texture.h"

bool D3D11Texture::Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta)
{
	ASSERT(images, "�����l image�ɒl������Ă��������B");

	auto hr = DirectX::CreateShaderResourceView(
		GetDevice(),
		images, imageSize, meta,
		m_shaderResourceView.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("ShaderResourceView �̐����Ɏ��s���܂����B");
		return false;
	}
	return true;
}

void D3D11Texture::PSSet(UINT slot /* = 0 */) const noexcept
{
	GetContext()->PSSetShaderResources(slot, 1, m_shaderResourceView.GetAddressOf());
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