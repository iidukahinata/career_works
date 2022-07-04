/**
* @file    Material.h
* @brief
*
* @date	   2022/07/01 2022年度初版
*/
#pragma once


#include <string_view>
#include "Texture.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

class Material : public IResource
{
	SUB_CLASS(Material)
public:

	Material();

	/** 独自モデルデータとして保存させる。*/
	void SaveToFile(std::string_view filePath) override;

	/** 独自モデルデータを読み込みする。*/
	bool LoadFromFile(std::string_view filePath) override;

	void AddTexture(Texture* texture) noexcept;

	/** 各シェーダー設定の変更。*/
	void SetVSShader(std::string_view name);
	void SetPSShader(std::string_view name);

	void ShaderSet() noexcept;

protected:

	bool Do_Load(std::string_view filePath) override { return true; };

	std::string ConvertProprietaryFormat(std::string_view filePath) const noexcept;

private:

	std::vector<Texture*> m_textures;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;

	D3D11SamplerState m_samplerState;
};