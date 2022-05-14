/**
* @file	   DepthOfField.h
* @brief
*
* @date	   2022/04/22 2022年度初版
* @author  飯塚陽太
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

	// * 被写界深度のぼかし作成
	Blur m_blur;

	// * 被写界深度処理を行う
	Sprite m_afterBlurSprite;

	// * オフスクリーンテクスチャをそのまま描画
	Sprite m_normalSprite;

	D3D11RenderTexture m_renderTexture;
};