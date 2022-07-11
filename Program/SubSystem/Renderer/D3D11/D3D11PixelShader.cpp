/**
* @file    D3D11PixelShader.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "D3D11Shader.h"

bool D3D11PixelShader::Create(
	StringView shader,
	D3D_SHADER_MACRO* macro /*  = nullptr */,
	StringView entrypoint /* = "main" */,
	StringView target /* = "ps_5_0" */
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
		LOG_ERROR(String(shader) + " : PixelShader�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}

void D3D11PixelShader::PSSet() const noexcept
{
	GetContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}