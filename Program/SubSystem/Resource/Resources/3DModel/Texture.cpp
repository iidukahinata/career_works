/**
* @file    Texture.cpp
* @brief
*
* @date	   2022/07/27 2022年度初版
*/


#include "Texture.h"
#include "SubSystem/Resource/ResourceLoader/TextureLoader/TextureLoader.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

void Texture::SaveToFile(StringView filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream;
	if (!fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode))
		return;

	fileStream.Write(m_textureData->m_imageCount);
	fileStream.Write(m_textureData->m_rowPitch);
	fileStream.Write(m_textureData->m_slicePitch);
	fileStream.Write(m_textureData->m_pixels);
	fileStream.Write(m_textureData->m_meta);
	
	m_textureData.Reset();
}

bool Texture::LoadFromFile(StringView filePath)
{
	auto path = ConvertProprietaryFormat(filePath);
	
	FileStream fileStream;
	if (!fileStream.Load(path, OpenMode::Read_Mode))
		return false;
	
	TextureData textureData;
	fileStream.Read(&textureData.m_imageCount);
	fileStream.Read(&textureData.m_rowPitch);
	fileStream.Read(&textureData.m_slicePitch);
	fileStream.Read(&textureData.m_pixels);
	fileStream.Read(&textureData.m_meta);
	
	return Create(textureData);
}

bool Texture::Create(TextureData& textureData) noexcept
{
	m_textureData = MakeUnique<TextureData>(textureData);

	Vector<DirectX::Image> images(textureData.m_imageCount);
	for (int i = 0; i < textureData.m_imageCount; ++i)
	{
		images[i].width		 = textureData.m_meta.width;
		images[i].height	 = textureData.m_meta.height;
		images[i].format	 = textureData.m_meta.format;
		images[i].rowPitch	 = textureData.m_rowPitch;
		images[i].slicePitch = textureData.m_slicePitch;
		images[i].pixels	 = &textureData.m_pixels[textureData.m_slicePitch * i];
	}

	return Create(images.data(), textureData.m_imageCount, textureData.m_meta);
}

bool Texture::Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta)
{
	return m_texture.Create(images, imageSize, meta);
}

void* Texture::GetResource() const noexcept
{
	return m_texture.Get();
}

bool Texture::Do_Load(StringView filePath)
{
	TextureLoader loader;
	return loader.Load(this, filePath);
}

String Texture::ConvertProprietaryFormat(StringView filePath) const noexcept
{
	String path = "assets/Resource/Texture/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	StringView sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".texture";

	return path;
}