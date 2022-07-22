/**
* @file		Texture.h
* @brief
*
* @date		2022/07/06 2022年度初版
*/
#pragma once


#include "../IResource.h"
#include "SubSystem/Renderer/D3D11/D3D11Texture.h"
#include "SubSystem/Renderer/D3D12/D3D12Texture.h"

struct TextureData
{
	size_t m_imageCount;
	size_t m_rowPitch;
	size_t m_slicePitch;
	Vector<uint8_t> m_pixels;

	DirectX::TexMetadata m_meta;
};

/**
* 各テクスチャデータを混合して扱えるようにするクラス。
*/
class Texture : public IResource
{
	SUB_CLASS(Texture)
public:

	Texture() = default;

	/** 独自テクスチャデータとして保存させる。*/
	void SaveToFile(StringView filePath) override;

	/** 独自テクスチャデータを読み込みする。*/
	bool LoadFromFile(StringView filePath) override;

	bool Create(TextureData& textureData) noexcept;
	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta);

	void PSSet(int slot) const noexcept;

private:

	// IResource
	bool Do_Load(StringView filePath) override;

	String ConvertProprietaryFormat(StringView filePath) const noexcept;

private:

	//* 独自データがない場合しか使用されない。
	//* もっといい実装があると思うので今後変更予定。
	UniquePtr<TextureData> m_textureData;

	D3D11Texture m_d3d11Texture;
	D3D12Texture m_d3d12Texture;
};