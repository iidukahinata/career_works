/**
* @file    Texture.cpp
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/


#include "Texture.h"
#include "SubSystem/IOStream/FileStream.h"
#include "SubSystem/Resource/ResourceLoader/TextureLoader/TextureLoader.h"

bool Texture::Create(DirectX::ScratchImage* image)
{
	if (image)
	{
		return Create(image->GetImages(), image->GetImageCount(), image->GetMetadata());
	}
	return false;
}

bool Texture::Do_Load(std::string_view filePath)
{
	// 独自データを調べる
	if (LoadFromFile(filePath))
		return true;

	TextureLoader loader;
	m_image = loader.Load(filePath);

	Create(m_image);

	// 次回から高速に読み込むために独自データを作成
	SaveToFile(filePath);

	return true;
}

void Texture::SaveToFile(std::string_view filePath)
{
	// ファイル拡張子を独自ファイル用に変更
	std::string path(filePath.substr(0, filePath.find(".")));
	path += ".bin";

	FileStream fileStream;
	if (!fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode))
		return;

	fileStream.Write(m_image->GetImageCount());
	fileStream.Write(m_image->GetImages()->rowPitch);
	fileStream.Write(m_image->GetImages()->slicePitch);
	fileStream.Write(m_image->GetPixelsSize());
	fileStream.Write(m_image->GetImages()->pixels, m_image->GetPixelsSize());
	fileStream.Write(m_image->GetMetadata());

	m_image = nullptr;
}

bool Texture::LoadFromFile(std::string_view filePath)
{
	// ファイル拡張子を独自ファイル用に変更
	std::string path(filePath.substr(0, filePath.find(".")));
	path += ".bin";

	FileStream fileStream;
	if (!fileStream.Load(path, OpenMode::Read_Mode))
		return false;

	TextureBase textureBase;
	fileStream.Read(&textureBase.m_imageCount);
	fileStream.Read(&textureBase.m_rowPitch);
	fileStream.Read(&textureBase.m_slicePitch);
	fileStream.Read(&textureBase.m_pixels);
	fileStream.Read(&textureBase.m_meta);

	std::vector<DirectX::Image> images(textureBase.m_imageCount);
	for (int i = 0; i < textureBase.m_imageCount; ++i)
	{
		images[i].width = textureBase.m_meta.width;
		images[i].height = textureBase.m_meta.height;
		images[i].format = textureBase.m_meta.format;
		images[i].rowPitch = textureBase.m_rowPitch;
		images[i].slicePitch = textureBase.m_slicePitch;
		images[i].pixels = &textureBase.m_pixels[textureBase.m_slicePitch * i];
	}
	
	return Create(images.data(), textureBase.m_imageCount, textureBase.m_meta);
}