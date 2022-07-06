/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/07/06 2022”N“x‰”Å
*/


#include "Renderer.h"

void Renderer::AddLight(Light* light) noexcept
{
	m_lightMap->AddLight(light);
}

void Renderer::RemoveLight(Light* light) noexcept
{
	m_lightMap->RemoveLight(light);
}

void Renderer::AddCamera(Camera* camera) noexcept
{
	if (!m_mainCamera)
	{
		m_mainCamera = camera;
	}

	m_cameras.insert(camera);
}

void Renderer::RemoveCamera(Camera* camera) noexcept
{
	m_cameras.erase(camera);
}

Camera* Renderer::GetMainCamera() const noexcept
{
	return m_mainCamera;
}

void Renderer::AddRenderObject(RenderObject* rederObject) noexcept
{
	m_renderObjects.insert(rederObject);
}

void Renderer::RemoveRenderObject(RenderObject* rederObject) noexcept
{
	m_renderObjects.erase(rederObject);
}

void Renderer::RegisterPostProcess(PostProcessEffect* postProcess) noexcept
{
	m_postProcessEffect = postProcess;
}

void Renderer::OnRegisterPostProcess(PostProcessEffect* postProcess) noexcept
{
	if (m_postProcessEffect == postProcess)
	{
		m_postProcessEffect = nullptr;
	}
}