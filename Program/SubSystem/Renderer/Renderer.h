/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/06/25 2022îNìxèâî≈
*/
#pragma once


#include "LightMap.h"
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class RenderObject;

class Renderer : public ISubsystem
{
	SUB_CLASS(Renderer)
public:

	Renderer();

	bool Initialize() override;
	void Shutdown() override;

	void RegisterRenderObject(RenderObject* rederObject) noexcept;
	void RemoveRenderObject(RenderObject* rederObject) noexcept;

	LightMap& GetLightMap();

private:

	void Update() noexcept;

	void BeginFream();
	void EndFream();

private:

	Job m_job;

	LightMap m_lightMap;

	std::vector<RenderObject*> m_renderObjects;
};