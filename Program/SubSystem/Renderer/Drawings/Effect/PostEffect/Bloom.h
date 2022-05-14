/**
* @file	   Bloom.h
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
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

	// * 輝度抽象を行う
	Sprite m_luminanceSprite;

	// * ブルーム処理を行う
	Sprite m_afterBlurSprite;

	// * オフスクリーンテクスチャをそのまま描画
	Sprite m_normalSprite;

	D3D11RenderTexture m_renderTexture;
};