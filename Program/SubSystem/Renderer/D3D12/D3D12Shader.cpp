/**
* @file    D3D12Shader.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "D3D12Shader.h"
#include <d3dcompiler.h>

void D3D12Shader::Compile(String_View filePath, String_View entryPoint, String_View traget) noexcept
{
#ifdef _DEBUG
	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT compileFlags = 0;
#endif // DEBUG

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		ToWstring(filePath).data(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint.data(), traget.data(),
		compileFlags, 0,
		m_blob.ReleaseAndGetAddressOf(),
		errorBlob.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			LOG_ERROR("指定されたファイルが見つかりませんでした。: Shader.cpp");
			return;
		}
		if (errorBlob) 
		{
			String error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), error.begin());
			error += "\n";
			LOG_ERROR(error.data());
		}
	}
}