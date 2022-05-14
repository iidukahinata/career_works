/**
* @file		TextureLoader.h
* @brief
*
* @date		2022/05/06 2022�N�x����
* @author	�ђ˗z��
*/
#pragma once


#include "ThirdParty/directxtex/include/DirectXTex.h"

class TextureLoader
{
public:

	DirectX::ScratchImage* Load(std::string_view filePath) noexcept;

private:

	std::unique_ptr<DirectX::ScratchImage> m_image;
};