/**
* @file	   ForwardRenderer.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "ForwardRenderer.h"
#include "SubSystem/Editer/EditerSystem.h"
#include "SubSystem/Window/Window.h"
#include "../Forward/ForwardLightMap.h"
#include "../Deferred/ClusteredLightMap.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/D3D12/D3D12GrahicsDevice.h"
#include "SubSystem/Scene/Component/Components/Camera.h"
#include "SubSystem/Scene/Component/Components/RenderObject.h"

static void DrawFrameRate()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(210, 50), ImGuiCond_Once);

	ImGui::Begin("Frame Rate");
	ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

ForwardRenderer::ForwardRenderer()
{
	m_job.SetFunction([this](double) { Update(); }, FunctionType::Render);
	m_job.RegisterToJobSystem();

	m_widget.SetFunction(DrawFrameRate);
	m_widget.RegisterToEditerSystem();
}

bool ForwardRenderer::Initialize()
{
	const auto width = Window::Get().GetWindowWidth();
	const auto height = Window::Get().GetWindowHeight();

	// デバイス初期化
	D3D12GraphicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());
	D3D11GraphicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());

	m_lightMap = MakeUnique<ForwardLightMap>();
	//m_lightMap->Initialize();
	
	//TransformCBuffer::Get().Init();

	return true;
}

void ForwardRenderer::Shutdown()
{
	m_job.UnRegisterFromJobSystem();
}

void ForwardRenderer::Update() noexcept
{
	//TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrix().ToMatrixXM());
	//TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrix().ToMatrixXM());

	auto& grahicsDevice = D3D12GraphicsDevice::Get();

	grahicsDevice.BeginFrame();
	grahicsDevice.SetRenderTarget(grahicsDevice.GetRenderTarget(), grahicsDevice.GetDepthStencil());
	grahicsDevice.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	//m_lightMap->Update(m_mainCamera);
	
	//for (auto renderObject : m_renderObjects)
	//{
	//	renderObject->Render();
	//}
	
	EditerSystem::Get().Render();

	grahicsDevice.EndFrame();
	grahicsDevice.Present();
}