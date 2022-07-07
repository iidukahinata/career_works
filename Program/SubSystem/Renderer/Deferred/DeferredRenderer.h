/**
* @file	   DeferredRenderer.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "GBuffer.h"
#include "../Renderer.h"
#include "../Geometry/Quad.h"
#include "../D3D11/D3D11Shader.h"
#include "../D3D11/D3D11InputLayout.h"
#include "../D3D11/D3D11SamplerState.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class PostProcessEffect;

/**
* �x�������_�����O�p�C�v���C���𐧌䂵�܂��B
*/
class DeferredRenderer : public Renderer
{
	SUB_CLASS(DeferredRenderer)
public:

	DeferredRenderer();

	bool Initialize() override;
	void Shutdown() override;

	void Update() noexcept;

private:

	/** Gbuffer �̍쐬�B*/
	void GBufferPass() const noexcept;

	/** �쐬�����f�[�^���烉�C�g�v�Z�B*/
	void LightingPass() const noexcept;

	/** Effect �v�Z�B*/
	void FinalPass() noexcept;

	void Set2DCamera() const noexcept;

private:

	Quad m_quad;

	D3D11VertexShader m_vsShader;
	D3D11InputLayout m_inputLayout;
	D3D11PixelShader m_psShader;
	D3D11SamplerState m_samplerState;

	UniquePtr<GBuffer> m_gbuffer;

	Job m_job;
};