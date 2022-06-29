/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/06/29 2022îNìxèâî≈
*/
#pragma once


#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class Light;
class LightMap;
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

	void AddLight(Light* light) noexcept;
	void RemoveLight(Light* light) noexcept;

private:

	void Update() noexcept;

	void BeginFream();
	void EndFream();

private:

	Job m_job;

	std::unique_ptr<LightMap> m_lightMap;

	std::vector<RenderObject*> m_renderObjects;
};