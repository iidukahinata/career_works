/**
* @file    D3D11Shader.cpp
* @brief
*
* @date	   2022/06/25 2022年度初版
*/


#include <d3dcompiler.h>
#include "D3D11Shader.h"
#include "SubSystem/Core/Common/Tools.h"

bool D3D11Shader::CompileFromFile(std::string_view shader, D3D_SHADER_MACRO* macro, std::string_view entrypoint, std::string_view traget) noexcept
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	HRESULT hr;
	if (GetExt(shader) == "cso")
	{
		hr = D3DReadFileToBlob(ToWstring(shader).data(), m_blob.ReleaseAndGetAddressOf());

		if (FAILED(hr))
		{
			LOG_ERROR("Shader コンパイルに失敗。");
			return false;
		}
	}
	else
	{
		// shaderコンパイル
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
		hr = D3DCompileFromFile(
			ToWstring(shader).data(),
			macro,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypoint.data(),
			traget.data(),
			flags,
			0,
			m_blob.ReleaseAndGetAddressOf(),
			errorBlob.GetAddressOf());

		if (FAILED(hr))
		{
			LOG_ERROR((char*)errorBlob->GetBufferPointer());
			return false;
		}
	}
	return true;
}

ID3DBlob* D3D11Shader::GetBlob() const noexcept
{
	return m_blob.Get();
}