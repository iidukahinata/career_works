/**
* @file    D3D12Shader.h
* @brief
*
* @date	   2022/07/29 2022年度初版
*/
#pragma once


#include <vector>
#include <string>
#include <d3d12.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include "D3D12DeviceChild.h"

class D3D12Shader : public D3D12DeviceChild
{
public:

	D3D12Shader() = default;
	D3D12Shader(std::string_view filePath, std::string_view entryPoint, std::string_view traget);

	void Compile(std::string_view filePath, std::string_view entryPoint, std::string_view traget) noexcept;

	/** アクセス */
	ID3DBlob* GetBlob() const noexcept { return m_blob.Get(); }
	std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout() noexcept;

private:

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
	Microsoft::WRL::ComPtr<ID3D12ShaderReflection> m_reflection;
};