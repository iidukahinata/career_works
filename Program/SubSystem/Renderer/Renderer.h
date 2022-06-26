/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/06/25 2022îNìxèâî≈
*/
#pragma once


#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class Renderer : public ISubsystem
{
	SUB_CLASS(Renderer)
public:

	Renderer();

	bool Initialize() override;
	void Shutdown() override;

private:

	void Update() noexcept;

	void BeginFream();
	void EndFream();

private:

	Job m_job;
};