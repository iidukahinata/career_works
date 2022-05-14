/**
* @file	   Monotone.cpp
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/


#include "Monotone.h"
#include "SubSystem/Window/Window.h"

bool Monotone::Init(Texture* texture)
{
	// モノトーン用レンダーターゲット生成
	m_renderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(), 
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDRレンダリングを行うように32ビットモード

	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0							, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	SpriteDesc spriteDesc;
	spriteDesc.width = Window::Get().GetWindowWidth();
	spriteDesc.height = Window::Get().GetWindowHeight();
	spriteDesc.textures.emplace_back(texture);
	spriteDesc.layout = inputLayout;
	spriteDesc.layoutSize = ARRAYSIZE(inputLayout);
	spriteDesc.vsShader = "assets/Shader/TextureVS.cso";
	spriteDesc.psShader = "assets/Shader/MonotonePS.cso";
	m_sprite.Init(spriteDesc);

	return true;
}

void Monotone::Draw()
{
	m_renderTexture.SetRenderTarget();
	m_renderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// モノトーンエフェクトをかける
	m_sprite.Draw(Math::Matrix::Identity.ToMatrixXM());
}

Texture* Monotone::GetTexture()
{
	return m_renderTexture.GetTexture();
}