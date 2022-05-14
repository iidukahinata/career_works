/**
* @file    D3D12Shader.cpp
* @brief
*
* @date	   2022/04/22 2022�N�x����
* @author  �ђ˗z��
*/


#include "D3D12Shader.h"
#include <d3dcompiler.h>
#include "SubSystem/Tools/Tools.h"
#include "SubSystem/Log/DebugLog.h"

void D3D12Shader::Compile(const char* filePath, const char* entryPoint, const char* traget) noexcept
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
		entryPoint, traget,
		compileFlags, 0,
		m_blob.ReleaseAndGetAddressOf(),
		errorBlob.ReleaseAndGetAddressOf());

	if (FAILED(hr))
	{
		if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			LOG_ERROR("�w�肳�ꂽ�t�@�C����������܂���ł����B: Shader.cpp");
			return;
		}
		if (errorBlob) 
		{
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), error.begin());
			error += "\n";
			LOG_ERROR(error.data());
		}
	}
}