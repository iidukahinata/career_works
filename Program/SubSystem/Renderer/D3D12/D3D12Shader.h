/**
* @file    D3D12Shader.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12Shader : public D3D12DeviceChild
{
public:

	void Compile(String_View filePath, String_View entryPoint, String_View traget) noexcept;

	ID3DBlob* GetBlob() const noexcept { return m_blob.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
};