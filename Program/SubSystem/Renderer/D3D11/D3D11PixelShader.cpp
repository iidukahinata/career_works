/**
* @file    D3D11PixelShader.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "D3D11Shader.h"

bool D3D11PixelShader::Create(
	std::string_view shader,
	D3D_SHADER_MACRO* macro,
	std::string_view entrypoint /* = "main" */,
	std::string_view target /* = "ps_5_0" */
) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, macro, entrypoint, target))
	{
		return false;
	}

	// �s�N�Z���V�F�[�_�[����
	HRESULT hr = GetDevice()->CreatePixelShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_pixelShader.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(std::string(shader) + " : PixelShader�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}

void D3D11PixelShader::PSSet() const noexcept
{
	GetContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}