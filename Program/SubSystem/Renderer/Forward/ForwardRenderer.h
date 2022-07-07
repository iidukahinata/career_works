/**
* @file	   ForwardRenderer.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../Renderer.h"

/**
* フォワードレンダリングで描画を行う。
*/
class ForwardRenderer : public Renderer
{
	SUB_CLASS(ForwardRenderer)
public:

	ForwardRenderer();

	bool Initialize() override;
	void Shutdown() override;

	void Update() noexcept;

private:

	Job m_job;
};