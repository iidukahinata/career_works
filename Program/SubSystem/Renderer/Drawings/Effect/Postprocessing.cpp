/**
* @file	   Postprocessing.cpp
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/


#include "Postprocessing.h"
#include "SubSystem/Window/Window.h"

bool Postprocessing::Init()
{
	CreateRenderTextures();

	// �����l�̓I�t�X�N���[�������̂܂ܕ`�悷��
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

	// MRT�ɐ؂�ւ�
	D3D11GrahicsDevice::Get().SetRenderTargets(2, renderTargets, m_offscreenRenderTexture.GetDepthStencil());
	D3D11GrahicsDevice::Get().SetViewport(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight());

	// �I�t�X�N���[���N���A
	m_offscreenRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// �[�x�X�N���[���N���A
	m_depthRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));
}

void Postprocessing::Draw()
{
	// �G�t�F�N�g��������
	for (auto& postEffect : m_postEffects)
	{
		postEffect->Draw();
	}

	// �o�b�N�o�b�t�@�[�ɐ؂�ւ�
	D3D11GrahicsDevice::Get().SetRenderTarget(D3D11GrahicsDevice::Get().GetRenderTarget(), D3D11GrahicsDevice::Get().GetDepthStencil());
	D3D11GrahicsDevice::Get().SetViewport(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight());
	
	// �G�t�F�N�g�K�p��e�N�X�`����\��t��
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
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDR�����_�����O���s���悤��32�r�b�g���[�h

	m_depthRenderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(),
		DXGI_FORMAT_R32_FLOAT);	// HDR�����_�����O���s���悤��32�r�b�g���[�h
}

void Postprocessing::CreateSprite()
{
	// ���_���C�A�E�g�쐬
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