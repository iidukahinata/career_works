/**
* @file	   DeferredRenderer.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "../Renderer.h"
#include "../Geometry/Quad.h"

class GBuffer;
class PostProcessEffect;

/**
* �x�������_�����O�p�C�v���C���𐧌䂵�܂��B
*/
class DeferredRenderer : public Renderer
{
public:

	bool Initialize() override;

private:

	void Update() noexcept;

	/** Gbuffer �̐����B*/
	void FirstPass() noexcept;

	/** �쐬�����f�[�^���烉�C�g�v�Z�B*/
	void SecondPass() noexcept;

	/** ��ʕ`��B*/
	void FinalPass() noexcept;

private:

	Quad m_quad;

	UniquePtr<GBuffer> m_gbuffer;
};