/**
* @file    D3D12Shader.cpp
* @brief
*
* @date	   2022/07/26 2022�N�x����
*/


#include "D3D12Shader.h"
#include <d3dcompiler.h>

D3D12Shader::D3D12Shader(StringView filePath, StringView entryPoint, StringView traget)
{
	Compile(filePath, entryPoint, traget);
}

void D3D12Shader::Compile(StringView filePath, StringView entryPoint, StringView traget) noexcept
{
#ifdef _DEBUG
	const UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	const UINT compileFlags = 0;
#endif // DEBUG

	if (GetExt(filePath) == "cso")
	{
		auto hr = D3DReadFileToBlob(ToWstring(filePath).data(), m_blob.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			LOG_ERROR("�V�F�[�_�R���p�C���Ɏ��s�B: Shader.cpp");
			return;
		}
	}
	else
	{
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
		auto hr = D3DCompileFromFile(
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
				LOG_ERROR("�w�肳�ꂽ�t�@�C����������܂���ł����B: Shader.cpp");
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
}