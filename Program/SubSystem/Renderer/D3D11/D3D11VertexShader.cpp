/**
* @file    D3D11VertexShader.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "D3D11Shader.h"

bool D3D11VertexShader::Create(std::string_view shader, std::string_view entrypoint /* = "main" */, std::string_view target /* = "vs_5_0" */) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, entrypoint, target))
	{
		return false;
	}

	// �R���s���[�^�[�V�F�[�_�[����
	HRESULT hr = GetDevice()->CreateVertexShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_vertexShader.GetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(std::string(shader) + " : VertexShader�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}

void D3D11VertexShader::VSSet() const noexcept
{
	GetContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
}