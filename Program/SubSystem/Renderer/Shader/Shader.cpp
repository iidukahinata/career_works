#include "Shader.h"

bool Shader::SetShader(String_View name) noexcept
{
	if (m_vertexShader.Create(name, m_macros.data(), "VSMain"))
	{
		return m_pixelShader.Create(name, m_macros.data(), "PSMain");
	}

	return false;
}

bool Shader::SetInputLayout(InputLayoutType layoutType) noexcept
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_inputLayout.Create(vertexDesc, layoutType, m_vertexShader.GetBlob());

	return true;
}

void Shader::AddMacro(String_View name, String_View value) noexcept
{
	m_macros.emplace_back(D3D_SHADER_MACRO(name.data(), value.data()));
}