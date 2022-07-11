/**
* @file		TextureLoader.h
* @brief
*
* @date		2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "ThirdParty/directxtex/include/DirectXTex.h"

class Texture;

class TextureLoader
{
public:

	bool Load(Texture* texture, StringView filePath) noexcept;

private:

	bool LoadFromFile(StringView ext, WstringView path, DirectX::TexMetadata* meta, DirectX::ScratchImage& image) noexcept;
	bool CreateFromData(Texture* texture, DirectX::TexMetadata& meta, DirectX::ScratchImage* image) noexcept;
};