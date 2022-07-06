/**
* @file		TextureLoader.cpp
* @brief
*
* @date		2022/07/06 2022”N“x‰”Å
*/


#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include "TextureLoader.h"

bool TextureLoader::Load(Texture* texture, String_View filePath) noexcept
{
	DirectX::TexMetadata meta;
	auto image = std::make_unique<DirectX::ScratchImage>();

	if (LoadFromFile(GetExt(filePath), ToWstring(filePath), &meta, *image))
	{
		if (CreateFromData(texture, meta, image.get()))
		{
			return true;
		}
	}

	LOG_ERROR(std::string(filePath) + "‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ‚Å‚µ‚½B");
	return false;
}

bool TextureLoader::LoadFromFile(String_View ext, Wstring_View path, DirectX::TexMetadata* meta, DirectX::ScratchImage& image) noexcept
{
	HRESULT hr = S_FALSE;

	if (ext == "dds")
	{
		hr = DirectX::LoadFromDDSFile(path.data(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, meta, image);
	}
	else if (ext == "tga")
	{
		hr = DirectX::LoadFromTGAFile(path.data(), meta, image);
	}
	else  if (ext != "bin")
	{
		hr = DirectX::LoadFromWICFile(path.data(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, meta, image);
	}

	if (hr == S_FALSE) {
		return false;
	}
	return true;
}

bool TextureLoader::CreateFromData(Texture* texture, DirectX::TexMetadata& meta, DirectX::ScratchImage* image) noexcept
{
	if (!image) {
		return false;
	}

	TextureData textureData;
	textureData.m_imageCount	= image->GetImageCount();
	textureData.m_meta			= meta;
	textureData.m_rowPitch		= image->GetImages()->rowPitch;
	textureData.m_slicePitch	= image->GetImages()->slicePitch;

	auto size = sizeof(uint8_t) * image->GetPixelsSize();
	textureData.m_pixels.resize(image->GetPixelsSize());
	memcpy_s(textureData.m_pixels.data(), size, image->GetImages()->pixels, size);

	return texture->Create(textureData);
}