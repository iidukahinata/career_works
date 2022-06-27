/**
* @file    Texture.cpp
* @brief
*
* @date	   2022/06/27 2022年度初版
*/


#include "Texture.h"
#include "SubSystem/Core/IO/FileStream.h"
#include "SubSystem/Core/IO/FileSystem.h"
#include "SubSystem/Resource/ResourceLoader/TextureLoader/TextureLoader.h"

void Texture::SaveToFile(std::string_view filePath)
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
	
	m_textureData.reset();
}

bool Texture::LoadFromFile(std::string_view filePath)
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
	m_textureData = std::make_unique<TextureData>(textureData);

	std::vector<DirectX::Image> images(textureData.m_imageCount);
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
	return m_d3d11Texture.Create(images, imageSize, meta);
}

void Texture::PSSet(int slot) const noexcept
{
	m_d3d11Texture.PSSet(slot);
}

bool Texture::Do_Load(std::string_view filePath)
{
	TextureLoader loader;
	return loader.Load(this, filePath);
}

std::string Texture::ConvertProprietaryFormat(std::string_view filePath) const noexcept
{
	std::string path = "assets/Resource/Texture/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	std::string_view sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".texture";

	return path;
}