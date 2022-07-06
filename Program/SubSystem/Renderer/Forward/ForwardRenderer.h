/**
* @file	   ForwardRenderer.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "../Renderer.h"
#include "SubSystem/JobSystem/Sync/Job.h"

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