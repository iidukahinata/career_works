/**
* @file    D3D11VertexShader.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "D3D11Shader.h"

bool D3D11VertexShader::Create(
	String_View shader,
	D3D_SHADER_MACRO* macro /*  = nullptr */,
	String_View entrypoint /* = "main" */,
	String_View target /* = "vs_5_0" */
) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, macro, entrypoint, target))
	{
		return false;
	}

	// コンピューターシェーダー生成
	HRESULT hr = GetDevice()->CreateVertexShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_vertexShader.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(String(shader) + " : VertexShader作成に失敗。");
		return false;
	}
	return true;
}

void D3D11VertexShader::VSSet() const noexcept
{
	GetContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
}