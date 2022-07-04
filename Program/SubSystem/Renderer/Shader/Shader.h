#pragma once


#include "../D3D11/D3D11Shader.h"
#include "../D3D11/D3D11InputLayout.h"

/**
* Type は Geometry で定義されているもののみ用意。
* 右の代入値は要素数を表す。
*/
enum InputLayoutType
{
	Vertex2D = 2U,

	Vertex3D = 3U,

	VertexBump3D = 5U,
};

class Shader
{
public:

	bool SetShader(std::string_view name) noexcept;
	bool SetInputLayout(InputLayoutType layoutType) noexcept;

	void AddMacro(std::string_view name, std::string_view value) noexcept;

private:

	D3D11PixelShader m_pixelShader;
	D3D11VertexShader m_vertexShader;

	D3D11InputLayout m_inputLayout;

	std::vector<D3D_SHADER_MACRO> m_macros;
};