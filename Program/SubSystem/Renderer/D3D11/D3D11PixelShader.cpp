/**
* @file    D3D11PixelShader.cpp
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
*/


#include "D3D11Shader.h"
#include "SubSystem/Log/DebugLog.h"

bool D3D11PixelShader::Create(
	std::string_view shader,
	std::string_view entrypoint /* = "main" */,
	std::string_view target /* = "ps_5_0" */
) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, entrypoint, target))
	{
		return false;
	}

	// ピクセルシェーダー生成
	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreatePixelShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_pixelShader.GetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(std::string(shader) + " : PixelShader作成失敗 : D3D11PixelShader.cpp");
		return false;
	}
	return true;
}

void D3D11PixelShader::PSSet() const noexcept
{
	GetGraphicsDevice()->GetContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}