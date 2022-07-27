/**
* @file    Material.h
* @brief
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include "../IResource.h"
#include "SubSystem/Renderer/D3D12/D3D12Shader.h"
#include "SubSystem/Renderer/D3D12/D3D12PipelineState.h"
#include "SubSystem/Renderer/D3D12/D3D12RootSignature.h"
#include "SubSystem/Renderer/D3D12/D3D12DescriptorHeap.h"

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

	bool CreatePipelineState() noexcept;
	bool CreateRootSignature() noexcept;

private:

	Vector<Texture*> m_textures;

	// * shader object
	D3D12Shader m_vertexShader;
	D3D12Shader  m_pixelShader;
	D3D12PipelineState m_pipelineState;
	D3D12RootSignature m_rootSignature;
	D3D12DescriptorHeap m_descriptHeap;
};