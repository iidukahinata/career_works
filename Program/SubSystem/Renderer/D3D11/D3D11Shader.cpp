/**
* @file    D3D11Shader.cpp
* @brief
*
* @date	   2022/05/10 2022Nxล
* @author  ัหzพ
*/


#include "D3D11Shader.h"
#include <d3dcompiler.h>
#include "SubSystem/Log/DebugLog.h"
#include "SubSystem/Tools/Tools.h"

bool D3D11Shader::CompileFromFile(std::string_view shader, std::string_view entrypoint, std::string_view traget) noexcept
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	HRESULT hr;
	if (GetExt(shader) == "cso")
	{
		hr = D3DReadFileToBlob(ToWstring(shader).c_str(), m_blob.ReleaseAndGetAddressOf());
	}
	else
	{
		// shaderRpC
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
		hr = D3DCompileFromFile(
			ToWstring(shader).c_str(),
			nullptr,
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

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

ID3DBlob* D3D11Shader::GetBlob() const noexcept
{
	return m_blob.Get();
}