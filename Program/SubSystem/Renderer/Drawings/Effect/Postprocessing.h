/**
* @file	   Postprocessing.h
* @brief
*
* @date	   2022/05/10 2022年度初版
* @version 1.00
* @author  飯塚陽太
* @note
*/
#pragma once


#include "PostEffect/PostEffect.h"
#include "SubSystem/Renderer/D3D11/D3D11RenderTexture.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class Postprocessing
{
public:

	bool Init();
	void Update();
	void Draw();

	template<class T>
	void AddPostEffect();

	Texture* GetOffscreenTexture();
	Texture* GetDepthTexture();

private:

	void CreateRenderTextures();
	void CreateSprite();

private:

	std::vector<std::unique_ptr<PostEffect>> m_postEffects;

	// * エフェクト適用後に描画するスプライト
	Sprite m_sprite;

	D3D11RenderTexture m_offscreenRenderTexture;
	D3D11RenderTexture m_depthRenderTexture;

	// * エフェクト適用後のテクスチャデータを保持
	D3D11Texture m_texture;
};

template<class T>
inline void Postprocessing::AddPostEffect()
{
	auto postEffect = new T();
	postEffect->SetPostprocessing(this);

	if (m_postEffects.empty()) 
	{
		// オフスクリーンテクスチャを元に描画させる
		postEffect->Init(m_offscreenRenderTexture.GetTexture());
	}
	else 
	{
		// 最後のエフェクト適用後テクスチャを元に描画させる
		postEffect->Init(m_postEffects.back()->GetTextue());
	}

	// 最後に画面描画するTextureを取得
	m_texture = postEffect->GetTextue();

	m_postEffects.emplace_back(postEffect);
}