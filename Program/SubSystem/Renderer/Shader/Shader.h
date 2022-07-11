/**
* @file	   Shader.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "../D3D11/D3D11Shader.h"
#include "../D3D11/D3D11InputLayout.h"

class Shader
{
public:

	bool SetPSShader(StringView name) noexcept;
	bool SetVSShader(StringView name) noexcept;

	bool SetInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize) noexcept;

	void AddMacro(StringView name, StringView value) noexcept;

private:

	D3D11PixelShader m_pixelShader;
	D3D11VertexShader m_vertexShader;

	D3D11InputLayout m_inputLayout;

	Vector<D3D_SHADER_MACRO> m_macros;
};