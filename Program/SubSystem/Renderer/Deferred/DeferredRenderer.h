/**
* @file	   DeferredRenderer.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../Renderer.h"
#include "../Geometry/Quad.h"

class GBuffer;
class PostProcessEffect;

/**
* 遅延レンダリングパイプラインを制御します。
*/
class DeferredRenderer : public Renderer
{
public:

	bool Initialize() override;

private:

	void Update() noexcept;

	/** Gbuffer の生成。*/
	void FirstPass() noexcept;

	/** 作成したデータからライト計算。*/
	void SecondPass() noexcept;

	/** 画面描画。*/
	void FinalPass() noexcept;

private:

	Quad m_quad;

	UniquePtr<GBuffer> m_gbuffer;
};