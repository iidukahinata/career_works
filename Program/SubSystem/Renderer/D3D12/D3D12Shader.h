/**
* @file    D3D12Shader.h
* @brief
*
* @date	   2022/07/27 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12Shader : public D3D12DeviceChild
{
public:

	D3D12Shader() = default;
	D3D12Shader(StringView filePath, StringView entryPoint, StringView traget);

	void Compile(StringView filePath, StringView entryPoint, StringView traget) noexcept;

	/** アクセス */
	ID3DBlob* GetBlob() const noexcept { return m_blob.Get(); }
	D3D12_INPUT_LAYOUT_DESC GetInputLayout() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
};