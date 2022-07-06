/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "Geometry/Quad.h"
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class Light;
class GBuffer;
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

	void FirstPass();
	void SecondPass();

private:

	Job m_job;

	Quad m_quad;

	UniquePtr<GBuffer> m_gbuffer;
	UniquePtr<LightMap> m_lightMap;

	Set<RenderObject*> m_renderObjects;
};