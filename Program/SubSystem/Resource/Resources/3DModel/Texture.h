/**
* @file		Texture.h
* @brief
*
* @date		2022/06/25 2022�N�x����
*/
#pragma once


#include "../IResource.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

struct TextureBase
{
	size_t m_imageCount;
	size_t m_rowPitch;
	size_t m_slicePitch;
	std::vector<uint8_t> m_pixels;

	DirectX::TexMetadata m_meta;
};

/**
* �e�e�N�X�`���f�[�^���������Ĉ�����悤�ɂ���N���X�B
*/
class Texture : public IResource
{
public:

	Texture() = default;

	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta) 
	{
		return true;
	}

private:

	// IResource
	bool Do_Load(std::string_view filePath) override;

	/** �Ǝ��e�N�X�`���f�[�^�Ƃ��ĕۑ�������B */
	void SaveToFile(std::string_view filePath);

	/** �Ǝ��e�N�X�`���f�[�^��ǂݍ��݂���B */
	bool LoadFromFile(std::string_view filePath);

private:

	//* �Ǝ��f�[�^���Ȃ��ꍇ�����g�p����Ȃ��B
	//* �����Ƃ�������������Ǝv���̂ō���ύX�\��B
	DirectX::ScratchImage* m_image;
};