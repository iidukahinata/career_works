/**
* @file    Sprite.h
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "../3DModel/Mesh.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

/** Sprite の初期化時設定の項目構造体 */
struct SpriteDesc
{
	// * 値が設定されている時は何よりも優先されます。
	const char* filePath = nullptr;

	// * filePath の次に読み込まれます。
	std::vector<Texture*> textures;

	// * null 以外の値である必要があります。
	D3D11_INPUT_ELEMENT_DESC* layout = nullptr;

	// * layout 配列の要素数を指定してください。
	UINT layoutSize = 0;

	// * 使用するシェーダーパスを指定してください。
	const char* vsShader = "assets/Shader/TextureVS.cso";
	const char* psShader = "assets/Shader/TexturePS.cso";

	// * テクスチャサイズを指定してください。
	float width = 1.f;
	float height = 1.f;
};

/** 表裏が存在しないテクスチャです。 */
class Sprite
{
public:

	Math::Vector4 m_color;

public:

	Sprite();

	void Init(const SpriteDesc& desc);
	void Draw(const DirectX::XMMATRIX& world);

private:

	Mesh<Vertex2D> m_mesh;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;
	D3D11SamplerState m_samplerState;
};