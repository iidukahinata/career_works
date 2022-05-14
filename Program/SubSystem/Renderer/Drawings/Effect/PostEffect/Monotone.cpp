/**
* @file	   Monotone.cpp
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/


#include "Monotone.h"
#include "SubSystem/Window/Window.h"

bool Monotone::Init(Texture* texture)
{
	// ���m�g�[���p�����_�[�^�[�Q�b�g����
	m_renderTexture.Create(
		Window::Get().GetWindowWidth(),
		Window::Get().GetWindowHeight(), 
		DXGI_FORMAT_R32G32B32A32_FLOAT);	// HDR�����_�����O���s���悤��32�r�b�g���[�h

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

	// ���m�g�[���G�t�F�N�g��������
	m_sprite.Draw(Math::Matrix::Identity.ToMatrixXM());
}

Texture* Monotone::GetTexture()
{
	return m_renderTexture.GetTexture();
}