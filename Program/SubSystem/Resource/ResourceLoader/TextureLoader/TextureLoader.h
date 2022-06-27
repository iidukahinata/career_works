/**
* @file		TextureLoader.h
* @brief
*
* @date		2022/06/26 2022îNìxèâî≈
*/
#pragma once


#include "ThirdParty/directxtex/include/DirectXTex.h"
#include "SubSystem/Resource/Resources/3DModel/Texture.h"

class TextureLoader
{
public:

	bool Load(Texture* texture, std::string_view filePath) noexcept;

private:

	bool LoadFromFile(std::string_view ext, std::wstring_view path, DirectX::TexMetadata* meta, DirectX::ScratchImage& image) noexcept;
	bool CreateFromData(Texture* texture, DirectX::TexMetadata& meta, DirectX::ScratchImage* image) noexcept;
};