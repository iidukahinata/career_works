/**
* @file	   DepthOfField.cpp
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
*/


#include "DepthOfField.h"
#include "../Postprocessing.h"
#include "SubSystem/Window/Window.h"

bool DepthOfField::Init(Texture* texture)
{
	m_blur.Init(texture);
	m_blur.SetVariance(10);

	CreateRenderTextures();

	CreateSprites(texture);

	return true;
}

void DepthOfField::Draw()
{
	m_blur.Draw();

	m_renderTexture.SetRenderTarget();
	m_renderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	m_normalSprite.Draw(Math::Matrix::Identity.ToMatrixXM());

	// 上から加算合成するため深度のみクリア
	D3D11GrahicsDevice::Get().GetContext()->ClearDepthStencilView(m_renderTexture.GetDepthStencil(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	m_afterBlurSprite.Draw(Math::Matrix::Identity.ToMatrixXM());
}

Texture* DepthOfField::GetTexture()
{
	return m_renderTexture.GetTexture();
}

void DepthOfField::CreateRenderTextures()
{
	m_renderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(),
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDRレンダリングを行うように32ビットモード
}

void DepthOfField::CreateSprites(Texture* texture)
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
	spriteDesc.vsShader = "assets/Shader/TextureVS.cso";

	// 通常レンダリング用 スプライト生成
	spriteDesc.textures.clear();
	spriteDesc.textures.emplace_back(texture);
	spriteDesc.psShader = "assets/Shader/TexturePS.cso";
	m_normalSprite.Init(spriteDesc);

	// 深度付きボケレンダリング用 スプライト生成
	spriteDesc.textures.clear();
	spriteDesc.textures.emplace_back(m_blur.GetTexture());
	spriteDesc.textures.emplace_back(m_postprocessing->GetDepthTexture());
	spriteDesc.psShader = "assets/Shader/DepthOfFieldPS.cso";
	m_afterBlurSprite.Init(spriteDesc);
}