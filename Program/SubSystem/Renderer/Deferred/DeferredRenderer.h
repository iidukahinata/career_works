/**
* @file	   DeferredRenderer.h
* @brief
*
* @date	   2022/07/24 2022�N�x����
*/
#pragma once


#include "GBuffer.h"
#include "../Renderer.h"
#include "../Geometry/Quad.h"
#include "../D3D11/D3D11Shader.h"
#include "../D3D11/D3D11InputLayout.h"
#include "../D3D11/D3D11SamplerState.h"
#include "../D3D11/D3D11RenderTexture.h"

class PostProcessEffect;

/**
* �x�������_�����O�ŕ`����s���B
*/
class DeferredRenderer : public Renderer
{
	SUB_CLASS(DeferredRenderer)
public:

	DeferredRenderer();

	bool Initialize() override;
	void Shutdown() override;

	/**
	* 22/07/24���_�ł� RederingThread �ő��삳��Ă��邪�A
	* �֐����̈ꕔ������ GameThread �Ɏ������������� TaskThread �̍쐬���������Ă���B
	* ��ɁA�萔�o�b�t�@�̍X�V�Ȃǂ���������B
	*/
	void Update() noexcept;

private:

	/** Gbuffer �̍쐬�B*/
	void GBufferPass() const noexcept;

	/** �쐬�����f�[�^���烉�C�g�v�Z�B*/
	void LightingPass() noexcept;

	/** Effect �v�Z�B*/
	void FinalPass() noexcept;

	void Set2DCamera() const noexcept;

private:

	UniquePtr<GBuffer> m_gbuffer;

	// * render texture
	D3D11RenderTexture m_renderTexture;
	
	// * deferred shader
	D3D11VertexShader m_deferredVSShader;
	D3D11InputLayout m_deferredInputLayout;
	D3D11PixelShader m_deferredPSShader;

	// * sprite shader
	D3D11VertexShader m_vsShader;
	D3D11InputLayout m_inputLayout;
	D3D11PixelShader m_psShader;
	D3D11SamplerState m_samplerState;

	Quad m_quad;

	Job m_job;

	Widget m_widget;
};