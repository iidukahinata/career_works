/**
* @file		TextureLoader.cpp
* @brief
*
* @date		2022/05/06 2022年度初版
* @author	飯塚陽太
*/


#include "TextureLoader.h"
#include <chrono>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include "SubSystem/Core/Common/Tools.h"
#include "SubSystem/Core/Common/Common.h"

DirectX::ScratchImage* TextureLoader::Load(std::string_view filePath) noexcept
{
	HRESULT hr = S_FALSE;

	// 指定文字列をwcharに変換
	auto ret = ToWstring(filePath);

	DirectX::TexMetadata meta;
	m_image = std::make_unique<DirectX::ScratchImage>();

	auto extname = GetExt(filePath);
	if (extname == "dds")
	{
		hr = DirectX::LoadFromDDSFile(ret.data(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, &meta, *m_image);
	}
	else if (extname == "tga")
	{
		hr = DirectX::LoadFromTGAFile(ret.data(), &meta, *m_image);
	}
	else  if (extname != "bin")
	{
		hr = DirectX::LoadFromWICFile(ret.data(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &meta, *m_image);
	}

	if (FAILED(hr)) {
		LOG_ERROR(std::string(filePath) + "が読み込めませんでした。");
		return nullptr;
	}
	return m_image.get();
}