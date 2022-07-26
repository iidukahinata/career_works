/**
* @file    D3D12Shader.h
* @brief
*
* @date	   2022/07/26 2022îNìxèâî≈
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include <string>
#include "D3D12DeviceChild.h"

class D3D12Shader : public D3D12DeviceChild
{
public:

	D3D12Shader() = default;
	D3D12Shader(StringView filePath, StringView entryPoint, StringView traget);

	void Compile(StringView filePath, StringView entryPoint, StringView traget) noexcept;

	ID3DBlob* GetBlob() const noexcept { return m_blob.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
};