/**
* @file	   ForwardRenderer.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "../Renderer.h"

/**
* �t�H���[�h�����_�����O�ŕ`����s���B
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