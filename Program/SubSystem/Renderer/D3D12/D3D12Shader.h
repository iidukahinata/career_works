/**
* @file    D3D12Shader.h
* @brief
*
* @date	   2022/05/13 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12Shader : public D3D12DeviceChild
{
public:

	void Compile(const char* filePath, const char* entryPoint, const char* traget) noexcept;

	ID3DBlob* GetBlob() const noexcept { return m_blob.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
};