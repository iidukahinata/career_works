/**
* @file    D3D11VertexShader.cpp
* @brief
*
* @date	   2022/04/29 2022年度初版
* @author  飯塚陽太
*/


#include "D3D11Shader.h"
#include "D3D11GrahicsDevice.h"
#include "SubSystem/Log/DebugLog.h"

bool D3D11VertexShader::Create(std::string_view shader, std::string_view entrypoint /* = "main" */, std::string_view target /* = "vs_5_0" */) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, entrypoint, target))
	{
		return false;
	}

	// コンピューターシェーダー生成
	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateVertexShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_vertexShader.GetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(std::string(shader) + " : VertexShader作成失敗 : D3D11VertexShader.cpp");
		return false;
	}
	return true;
}

void D3D11VertexShader::VSSet() const noexcept
{
	GetGraphicsDevice()->GetContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
}