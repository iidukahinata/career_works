/**
* @file    Material.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../IResource.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

class Texture;

class Material : public IResource
{
	SUB_CLASS(Material)
public:

	Material();

	/** 独自モデルデータとして保存させる。*/
	void SaveToFile(StringView filePath) override;

	/** 独自モデルデータを読み込みする。*/
	bool LoadFromFile(StringView filePath) override;

	void AddTexture(Texture* texture) noexcept;

	/** 各シェーダー設定の変更。*/
	void SetVSShader(StringView name);
	void SetPSShader(StringView name);

	void ShaderSet() const noexcept;

protected:

	bool Do_Load(StringView filePath) override { return true; };

	String ConvertProprietaryFormat(StringView filePath) const noexcept;

private:

	Vector<Texture*> m_textures;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;

	D3D11SamplerState m_samplerState;
};