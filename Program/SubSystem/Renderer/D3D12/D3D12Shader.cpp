/**
* @file    D3D12Shader.cpp
* @brief
*
* @date	   2022/07/27 2022年度初版
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
			LOG_ERROR("シェーダコンパイルに失敗。: Shader.cpp");
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
}

D3D12_INPUT_LAYOUT_DESC D3D12Shader::GetInputLayout() const noexcept
{
	Microsoft::WRL::ComPtr<ID3D12ShaderReflection> reflection;
	D3DReflect(m_blob->GetBufferPointer(), m_blob->GetBufferSize()
		, IID_PPV_ARGS(reflection.ReleaseAndGetAddressOf()));

	D3D12_SHADER_DESC shaderDesc;
	reflection->GetDesc(&shaderDesc);

	Vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescs;
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		D3D12_SIGNATURE_PARAMETER_DESC paramDesc;
		reflection->GetInputParameterDesc(i, &paramDesc);

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
				inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		inputElementDescs.push_back(inputElementDesc);
	}

	D3D12_INPUT_LAYOUT_DESC result;
	result.NumElements = inputElementDescs.size();
	result.pInputElementDescs = inputElementDescs.data();
	return result;
}