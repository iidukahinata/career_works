/**
* @file	   DeferredRenderer.h
* @brief
*
* @date	   2022/07/06 2022年度初版
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
* 遅延レンダリングで描画を行う。
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

	/** Gbuffer の作成。*/
	void GBufferPass() const noexcept;

	/** 作成したデータからライト計算。*/
	void LightingPass() noexcept;

	/** Effect 計算。*/
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