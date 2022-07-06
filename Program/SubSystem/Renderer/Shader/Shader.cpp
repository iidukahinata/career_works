/**
* @file	   Shader.cpp
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/


#include "Shader.h"

bool Shader::SetPSShader(String_View name) noexcept
{
	return m_pixelShader.Create(name, m_macros.data(), "main");
}

bool Shader::SetVSShader(String_View name) noexcept
{
	return m_vertexShader.Create(name, m_macros.data(), "main");
}

bool Shader::SetInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize) noexcept
{
	return 	m_inputLayout.Create(layout, layoutSize, m_vertexShader.GetBlob());;
}

void Shader::AddMacro(String_View name, String_View value) noexcept
{
	m_macros.emplace_back(D3D_SHADER_MACRO(name.data(), value.data()));
}