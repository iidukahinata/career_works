/**
* @file	   Postprocessing.cpp
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/


#include "Postprocessing.h"
#include "SubSystem/Window/Window.h"

bool Postprocessing::Init()
{
	CreateRenderTextures();

	// 初期値はオフスクリーンをそのまま描画する
	m_texture = *m_offscreenRenderTexture.GetTexture();

	CreateSprite();

	return true;
}

void Postprocessing::Update()
{
	ID3D11RenderTargetView* renderTargets[] = {
		m_offscreenRenderTexture.GetRenderTarget(),
		m_depthRenderTexture.GetRenderTarget()
	};

	// MRTに切り替え
	D3D11GrahicsDevice::Get().SetRenderTargets(2, renderTargets, m_offscreenRenderTexture.GetDepthStencil());
	D3D11GrahicsDevice::Get().SetViewport(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight());

	// オフスクリーンクリア
	m_offscreenRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// 深度スクリーンクリア
	m_depthRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));
}

void Postprocessing::Draw()
{
	// エフェクトをかける
	for (auto& postEffect : m_postEffects)
	{
		postEffect->Draw();
	}

	// バックバッファーに切り替え
	D3D11GrahicsDevice::Get().SetRenderTarget(D3D11GrahicsDevice::Get().GetRenderTarget(), D3D11GrahicsDevice::Get().GetDepthStencil());
	D3D11GrahicsDevice::Get().SetViewport(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight());
	
	// エフェクト適用後テクスチャを貼り付け
	m_sprite.Draw(Math::Matrix::Identity.ToMatrixXM());
}

Texture* Postprocessing::GetOffscreenTexture()
{
	return m_offscreenRenderTexture.GetTexture();
}

Texture* Postprocessing::GetDepthTexture()
{
	return m_depthRenderTexture.GetTexture();
}

void Postprocessing::CreateRenderTextures()
{
	m_offscreenRenderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(),
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDRレンダリングを行うように32ビットモード

	m_depthRenderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(),
		DXGI_FORMAT_R32_FLOAT);	// HDRレンダリングを行うように32ビットモード
}

void Postprocessing::CreateSprite()
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0							, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	SpriteDesc spriteDesc;
	spriteDesc.width = Window::Get().GetWindowWidth();
	spriteDesc.height = Window::Get().GetWindowHeight();
	spriteDesc.textures.emplace_back(&m_texture);
	spriteDesc.layout = inputLayout;
	spriteDesc.layoutSize = ARRAYSIZE(inputLayout);
	spriteDesc.vsShader = "assets/Shader/TextureVS.cso";
	spriteDesc.psShader = "assets/Shader/TexturePS.cso";
	m_sprite.Init(spriteDesc);
}