/**
* @file	   Postprocessing.h
* @brief
*
* @date	   2022/05/10 2022�N�x����
* @version 1.00
* @author  �ђ˗z��
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

	// * �G�t�F�N�g�K�p��ɕ`�悷��X�v���C�g
	Sprite m_sprite;

	D3D11RenderTexture m_offscreenRenderTexture;
	D3D11RenderTexture m_depthRenderTexture;

	// * �G�t�F�N�g�K�p��̃e�N�X�`���f�[�^��ێ�
	D3D11Texture m_texture;
};

template<class T>
inline void Postprocessing::AddPostEffect()
{
	auto postEffect = new T();
	postEffect->SetPostprocessing(this);

	if (m_postEffects.empty()) 
	{
		// �I�t�X�N���[���e�N�X�`�������ɕ`�悳����
		postEffect->Init(m_offscreenRenderTexture.GetTexture());
	}
	else 
	{
		// �Ō�̃G�t�F�N�g�K�p��e�N�X�`�������ɕ`�悳����
		postEffect->Init(m_postEffects.back()->GetTextue());
	}

	// �Ō�ɉ�ʕ`�悷��Texture���擾
	m_texture = postEffect->GetTextue();

	m_postEffects.emplace_back(postEffect);
}