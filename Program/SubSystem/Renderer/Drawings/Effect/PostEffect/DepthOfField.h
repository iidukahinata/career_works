/**
* @file	   DepthOfField.h
* @brief
*
* @date	   2022/04/22 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "Blur.h"

class DepthOfField : public PostEffect
{
public:

	bool Init(Texture* texture) override;
	void Draw() override;

	Texture* GetTexture() override;

private:

	void CreateRenderTextures();
	void CreateSprites(Texture* texture);

private:

	// * ��ʊE�[�x�̂ڂ����쐬
	Blur m_blur;

	// * ��ʊE�[�x�������s��
	Sprite m_afterBlurSprite;

	// * �I�t�X�N���[���e�N�X�`�������̂܂ܕ`��
	Sprite m_normalSprite;

	D3D11RenderTexture m_renderTexture;
};