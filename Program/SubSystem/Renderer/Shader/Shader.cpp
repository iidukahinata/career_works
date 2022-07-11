/**
* @file	   Shader.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "Shader.h"

bool Shader::SetPSShader(StringView name) noexcept
{
	return m_pixelShader.Create(name, m_macros.data(), "main");
}

bool Shader::SetVSShader(StringView name) noexcept
{
	return m_vertexShader.Create(name, m_macros.data(), "main");
}

bool Shader::SetInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize) noexcept
{
	return 	m_inputLayout.Create(layout, layoutSize, m_vertexShader.GetBlob());;
}

void Shader::AddMacro(StringView name, StringView value) noexcept
{
	m_macros.emplace_back(D3D_SHADER_MACRO(name.data(), value.data()));
}