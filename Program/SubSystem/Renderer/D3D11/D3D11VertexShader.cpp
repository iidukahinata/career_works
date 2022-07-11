/**
* @file    D3D11VertexShader.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "D3D11Shader.h"

bool D3D11VertexShader::Create(
	StringView shader,
	D3D_SHADER_MACRO* macro /*  = nullptr */,
	StringView entrypoint /* = "main" */,
	StringView target /* = "vs_5_0" */
) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, macro, entrypoint, target))
	{
		return false;
	}

	// �R���s���[�^�[�V�F�[�_�[����
	HRESULT hr = GetDevice()->CreateVertexShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_vertexShader.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(String(shader) + " : VertexShader�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}

void D3D11VertexShader::VSSet() const noexcept
{
	GetContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
}