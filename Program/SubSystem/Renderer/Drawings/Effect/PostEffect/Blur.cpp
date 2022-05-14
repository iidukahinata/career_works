/**
* @file	   Blur.cpp
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
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

	// �ڂ������������
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

	// �������u���[��������
	m_xBlurSprite.Draw(Math::Matrix::Identity.ToMatrixXM());

	m_yBlurRenderTexture.SetRenderTarget();
	m_yBlurRenderTexture.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// �c�����u���[��������
	m_yBlurSprite.Draw(Math::Matrix::Identity.ToMatrixXM());
}

Texture* Blur::GetTexture()
{
	return m_yBlurRenderTexture.GetTexture();
}

void Blur::SetVariance(float variance)
{
	// �V�����d�݃e�[�u���쐬
	CalculateWeightTablesFromGaussian(variance);

	// GPU�f�[�^���X�V
	ConstantBufferBlur buffer = {
		m_weights[0],m_weights[1],m_weights[2],m_weights[3],
		m_weights[4],m_weights[5],m_weights[6],m_weights[7],
		Math::Vector2(Window::Get().GetWindowWidth(), Window::Get().GetWindowHeight())
	};

	m_constantBuffer.Update(buffer);
}

void Blur::CreateRenderTextures(const Math::Vector2& textureSize)
{
	// x�u���[�p��RenderTarget����
	m_xBlurRenderTexture.Create(
		textureSize.x / 2,
		textureSize.y,
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDR�����_�����O���s���悤��32�r�b�g���[�h

	// y�u���[�p��RenderTarget����
	m_yBlurRenderTexture.Create(
		textureSize.x / 2,
		textureSize.y / 2,
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDR�����_�����O���s���悤��32�r�b�g���[�h
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

	// x�u���[�p �X�v���C�g����
	spriteDesc.textures.push_back(texture);
	spriteDesc.vsShader = "assets/Shader/XBlurVS.cso";
	m_xBlurSprite.Init(spriteDesc);

	// y�u���[�p �X�v���C�g����
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