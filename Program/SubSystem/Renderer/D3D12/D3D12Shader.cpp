/**
* @file    D3D12Shader.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "D3D12Shader.h"

std::wstring ToWstring(std::string_view str) noexcept
{
	// 変換後の文字列の長さを取得
	int lenght = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.reserve(lenght);

	// 文字列変換
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, &wstr[0], lenght);

	return wstr;
}

D3D12Shader::D3D12Shader(std::string_view filePath, std::string_view entryPoint, std::string_view traget)
{
	Compile(filePath, entryPoint, traget);
}

void D3D12Shader::Compile(std::string_view filePath, std::string_view entryPoint, std::string_view traget) noexcept
{
#ifdef _DEBUG
	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT compileFlags = 0;
#endif // DEBUG

	HRESULT hr;
	//if (GetExt(filePath) == "cso")
	//{
	//	hr = D3DReadFileToBlob(ToWstring(filePath).data(), m_blob.ReleaseAndGetAddressOf());
	//	if (FAILED(hr))
	//	{
	//		LOG_ERROR("シェーダコンパイルに失敗。: Shader.cpp");
	//		return;
	//	}
	//}
	//else
	{
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
				//LOG_ERROR("指定されたファイルが見つかりませんでした。: Shader.cpp");
				return;
			}
			if (errorBlob)
			{
				std::string error;
				error.resize(errorBlob->GetBufferSize());
				std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), error.begin());
				error += "\n";
				//LOG_ERROR(error.data());
			}
		}
	}
}

std::vector<D3D12_INPUT_ELEMENT_DESC> D3D12Shader::GetInputLayout() noexcept
{
	D3DReflect(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), IID_PPV_ARGS(m_reflection.ReleaseAndGetAddressOf()));

	D3D12_SHADER_DESC shaderDesc;
	m_reflection->GetDesc(&shaderDesc);

	std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescs;
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		D3D12_SIGNATURE_PARAMETER_DESC paramDesc;
		m_reflection->GetInputParameterDesc(i, &paramDesc);

		D3D12_INPUT_ELEMENT_DESC inputElementDesc;
		ZeroMemory(&inputElementDesc, sizeof(inputElementDesc));
		inputElementDesc.SemanticName = paramDesc.SemanticName;
		inputElementDesc.SemanticIndex = paramDesc.SemanticIndex;
		inputElementDesc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				inputElementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}

		inputElementDescs.push_back(std::move(inputElementDesc));
	}

	return inputElementDescs;
}