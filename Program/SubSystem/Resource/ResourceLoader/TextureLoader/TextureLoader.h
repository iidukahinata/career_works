/**
* @file		TextureLoader.h
* @brief
*
* @date		2022/07/06 2022�N�x����
*/
#pragma once


#include "ThirdParty/directxtex/include/DirectXTex.h"
#include "SubSystem/Resource/Resources/3DModel/Texture.h"

class TextureLoader
{
public:

	bool Load(Texture* texture, String_View filePath) noexcept;

private:

	bool LoadFromFile(String_View ext, std::wstring_view path, DirectX::TexMetadata* meta, DirectX::ScratchImage& image) noexcept;
	bool CreateFromData(Texture* texture, DirectX::TexMetadata& meta, DirectX::ScratchImage* image) noexcept;
};