/**
* @file	   Bloom.h
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "Blur.h"

class Bloom : public PostEffect
{
public:

	bool Init(Texture* texture) override;
	void Draw() override;

	Texture* GetTexture() override;

private:

	void CreateRenderTextures();
	void InitBlurs();
	void CreateSprites(Texture* texture);

private:

	Blur m_blur[4];

	// * �P�x���ۂ��s��
	Sprite m_luminanceSprite;

	// * �u���[���������s��
	Sprite m_afterBlurSprite;

	// * �I�t�X�N���[���e�N�X�`�������̂܂ܕ`��
	Sprite m_normalSprite;

	D3D11RenderTexture m_renderTexture;
};