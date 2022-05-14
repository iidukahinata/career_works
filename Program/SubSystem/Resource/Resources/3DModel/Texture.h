/**
* @file		Texture.h
* @brief
*
* @date		2022/05/11 2022年度初版
* @author	飯塚陽太
*/
#pragma once


#include "../IResource.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

struct TextureBase
{
	size_t m_imageCount;
	size_t m_rowPitch;
	size_t m_slicePitch;
	std::vector<uint8_t> m_pixels;

	DirectX::TexMetadata m_meta;
};

/**
* 各テクスチャデータを混合して扱えるようにするクラス。
*/
class Texture : public IResource
{
public:

	Texture() = default;

	bool Create(DirectX::ScratchImage* image);

	virtual bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta) { return true; };
	virtual void Bind(UINT slot = 0) {};

private:

	// IResource
	bool Do_Load(std::string_view filePath) override;

	/** 独自テクスチャデータとして保存させる。 */
	void SaveToFile(std::string_view filePath);

	/** 独自テクスチャデータを読み込みする。 */
	bool LoadFromFile(std::string_view filePath);

private:

	//* 独自データがない場合しか使用されない。
	//* もっといい実装があると思うので今後変更予定。
	DirectX::ScratchImage* m_image;
};