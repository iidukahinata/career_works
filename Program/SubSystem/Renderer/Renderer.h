/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/07/01 2022îNìxèâî≈
*/
#pragma once


#include <set>
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"
#include "Geometry/Quad.h"

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

	std::unique_ptr<GBuffer> m_gbuffer;
	std::unique_ptr<LightMap> m_lightMap;

	std::set<RenderObject*> m_renderObjects;
};