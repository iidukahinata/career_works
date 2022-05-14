/**
* @file    D3D11ComputeShader.cpp
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
*/


#include "D3D11Shader.h"
#include "SubSystem/Log/DebugLog.h"

bool D3D11ComputeShader::Create(
	std::string_view shader,
	std::string_view entrypoint /* = "main" */,
	std::string_view target /* = "gs_5_0" */
) noexcept
{
	// shader compile
	if (!CompileFromFile(shader, entrypoint, target))
	{
		return false;
	}

	// コンピューターシェーダー生成
	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateComputeShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_computeShader.GetAddressOf());

	if (FAILED(hr))
	{
		LOG_ERROR(std::string(shader) + " : ComputeShader作成失敗 : D3D11ComputeShader.cpp");
		return false;
	}
	return true;
}