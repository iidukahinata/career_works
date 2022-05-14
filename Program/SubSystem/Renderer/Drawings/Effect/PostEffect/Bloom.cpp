/**
* @file	   Bloom.cpp
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/


#include "Bloom.h"
#include "../Postprocessing.h"
#include "SubSystem/Window/Window.h"

bool Bloom::Init(Texture* texture)
{
	CreateRenderTextures();

	InitBlurs();

	CreateSprites(texture);

	return true;
}

void Bloom::Draw()
{
	m_renderTexture.SetRenderTarget();
	m_renderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	m_luminanceSprite.Draw(Math::Matrix::Identity.ToMatrixXM());

	// �P�x�e�N�X�`���Ƀu���[��������
	for (int i = 0; i < 4; ++i) {
		m_blur[i].Draw();
	}

	m_renderTexture.SetRenderTarget();
	m_renderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	m_normalSprite.Draw(Math::Matrix::Identity.ToMatrixXM());

	// �ォ����Z�������邽�ߐ[�x�̂݃N���A
	D3D11GrahicsDevice::Get().GetContext()->ClearDepthStencilView(m_renderTexture.GetDepthStencil(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	// �u�����h���[�h�����Z�����ɕύX
	auto& renderStates = D3D11GrahicsDevice::Get().GetRenderStates();
	renderStates.SetBlendState(renderStates.m_additiveBlend.Get());
	
	m_afterBlurSprite.Draw(Math::Matrix::Identity.ToMatrixXM());
	
	// �u�����h���[�h���A���t�@�u�����h�L���ɖ߂�
	renderStates.SetBlendState(renderStates.m_alphaEnabledBlend.Get());
}

Texture* Bloom::GetTexture()
{
	return nullptr;
}

void Bloom::CreateRenderTextures()
{
	m_renderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(),
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDR�����_�����O���s���悤��32�r�b�g���[�h
}

void Bloom::InitBlurs()
{
	// ���邢�������ڂ����p
	Math::Vector2 textureSize(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight());

	for (int i = 0; i < 4; ++i)
	{
		if (i == 0) {
			m_blur[i].Init(m_renderTexture.GetTexture(), textureSize);
		}
		else {
			m_blur[i].Init(m_blur[i - 1].GetTexture(), textureSize);
		}
		m_blur[i].SetVariance(20);
		textureSize *= 0.5f;
	}
}

void Bloom::CreateSprites(Texture* texture)
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

	// �ʏ탌���_�����O�p �X�v���C�g����
	spriteDesc.textures.clear();
	spriteDesc.textures.emplace_back(texture);
	spriteDesc.psShader = "assets/Shader/TexturePS.cso";
	m_normalSprite.Init(spriteDesc);

	// ���邳���o�p �X�v���C�g����
	spriteDesc.textures.emplace_back(texture);
	spriteDesc.psShader = "assets/Shader/LuminanceSamplingPS.cso";
	m_luminanceSprite.Init(spriteDesc);

	// �u���[�������p �X�v���C�g����
	spriteDesc.textures.clear();
	spriteDesc.textures.emplace_back(m_blur[0].GetTexture());
	spriteDesc.textures.emplace_back(m_blur[1].GetTexture());
	spriteDesc.textures.emplace_back(m_blur[2].GetTexture());
	spriteDesc.textures.emplace_back(m_blur[3].GetTexture());
	spriteDesc.psShader = "assets/Shader/BloomPS.cso";
	m_afterBlurSprite.Init(spriteDesc);
}