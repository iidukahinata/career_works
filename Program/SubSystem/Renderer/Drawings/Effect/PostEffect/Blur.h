/**
* @file	   Blur.h
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
* @note
*  ガウシアンブラーでのブラー処理実装
*/
#pragma once


#include "PostEffect.h"
#include "SubSystem/Renderer/D3D11/D3D11RenderTexture.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class Blur : public PostEffect
{
public:

	bool Init(Texture* texture) override;
	bool Init(Texture* texture, const Math::Vector2& textureSize);

	void Draw() override;

	Texture* GetTexture() override;

	void SetVariance(float variance);

private:

	void CreateRenderTextures(const Math::Vector2& textureSize);
	void CreateSprites(Texture* texture);

	void CalculateWeightTablesFromGaussian(float variance);

private:

	// * 横ブラー処理を行う
	Sprite m_xBlurSprite;

	// * 縦ブラー処理を行う
	Sprite m_yBlurSprite;

	D3D11RenderTexture m_xBlurRenderTexture;
	D3D11RenderTexture m_yBlurRenderTexture;

	// ガウシアンブラーの重み
	float m_weights[8];

	struct ConstantBufferBlur
	{
		float weights[8];
		Math::Vector2 screenSize;
	};

	D3D11ConstantBuffer<ConstantBufferBlur> m_constantBuffer;
};