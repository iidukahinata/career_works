/**
* @file	   Blur.cpp
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/


#include "Blur.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Tools/Tools.h"

#include"SubSystem/Input/Input.h"

bool Blur::Init(Texture* texture)
{
	Math::Vector2 textureSize(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight());

	return Init(texture, textureSize);
}

bool Blur::Init(Texture* texture, const Math::Vector2& textureSize)
{
	m_constantBuffer.Create(sizeof(ConstantBufferBlur));

	CreateRenderTextures(textureSize);

	CreateSprites(texture);

	// ぼかし具合を初期化
	SetVariance(10);

	return true;
}

void Blur::Draw()
{
	// set buffer
	m_constantBuffer.VSSet(2);
	m_constantBuffer.PSSet(2);

	m_xBlurRenderTexture.SetRenderTarget();
	m_xBlurRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// 横方向ブラーをかける
	m_xBlurSprite.Draw(Math::Matrix::Identity.ToMatrixXM());

	m_yBlurRenderTexture.SetRenderTarget();
	m_yBlurRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// 縦方向ブラーをかける
	m_yBlurSprite.Draw(Math::Matrix::Identity.ToMatrixXM());
}

Texture* Blur::GetTexture()
{
	return m_yBlurRenderTexture.GetTexture();
}

void Blur::SetVariance(float variance)
{
	// 新しく重みテーブル作成
	CalculateWeightTablesFromGaussian(variance);

	// GPUデータを更新
	ConstantBufferBlur buffer = {
		m_weights[0],m_weights[1],m_weights[2],m_weights[3],
		m_weights[4],m_weights[5],m_weights[6],m_weights[7],
		Math::Vector2(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight())
	};

	m_constantBuffer.Update(buffer);
}

void Blur::CreateRenderTextures(const Math::Vector2& textureSize)
{
	// xブラー用のRenderTarget生成
	m_xBlurRenderTexture.Create(
		textureSize.x / 2,
		textureSize.y,
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDRレンダリングを行うように32ビットモード

	// yブラー用のRenderTarget生成
	m_yBlurRenderTexture.Create(
		textureSize.x / 2,
		textureSize.y / 2,
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDRレンダリングを行うように32ビットモード
}

void Blur::CreateSprites(Texture* texture)
{
	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0							, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	SpriteDesc spriteDesc;
	spriteDesc.width = Window::Get().GetWindowWidth();
	spriteDesc.height = Window::Get().GetWindowHeight();
	spriteDesc.layout = inputLayout;
	spriteDesc.layoutSize = ARRAYSIZE(inputLayout);
	spriteDesc.psShader = "assets/Shader/BlurPS.cso";

	// xブラー用 スプライト生成
	spriteDesc.textures.push_back(texture);
	spriteDesc.vsShader = "assets/Shader/XBlurVS.cso";
	m_xBlurSprite.Init(spriteDesc);

	// yブラー用 スプライト生成
	spriteDesc.textures.clear();
	spriteDesc.textures.push_back(m_xBlurRenderTexture.GetTexture());
	spriteDesc.vsShader = "assets/Shader/YBlurVS.cso";
	m_yBlurSprite.Init(spriteDesc);
}

void Blur::CalculateWeightTablesFromGaussian(float variance)
{
	float weightSum = 0.f;
	for (int i = 0; i < 4; ++i)
	{
		m_weights[i] = expf(-0.5f * static_cast<float>(i * i) / variance);
		weightSum += 2.f * m_weights[i];
	}

	// normalize
	for (int i = 0; i < 8; ++i)
	{
		m_weights[i] /= weightSum;
	}
}