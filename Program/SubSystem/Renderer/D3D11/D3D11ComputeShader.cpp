/**
* @file    D3D11ComputeShader.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "D3D11Shader.h"

bool D3D11ComputeShader::Create(
	StringView shader,
	D3D_SHADER_MACRO* macro /*  = nullptr */,
	StringView entrypoint /* = "main" */,
	StringView target /* = "gs_5_0" */
) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, macro, entrypoint, target))
	{
		return false;
	}

	// �R���s���[�^�[�V�F�[�_�[����
	HRESULT hr = GetDevice()->CreateComputeShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_computeShader.GetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(String(shader) + " : ComputeShader�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}