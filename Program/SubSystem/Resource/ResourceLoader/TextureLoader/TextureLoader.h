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

	bool Load(Texture* texture, String_View filePath) noexcept;

private:

	bool LoadFromFile(String_View ext, Wstring_View path, DirectX::TexMetadata* meta, DirectX::ScratchImage& image) noexcept;
	bool CreateFromData(Texture* texture, DirectX::TexMetadata& meta, DirectX::ScratchImage* image) noexcept;
};