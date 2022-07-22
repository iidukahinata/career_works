/**
* @file	   ForwardRenderer.cpp
* @brief
*
* @date	   2022/07/08 2022年度初版
*/


#include "ForwardRenderer.h"
#include "SubSystem/Editer/EditerSystem.h"
#include "SubSystem/Window/Window.h"
#include "../Forward/ForwardLightMap.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "SubSystem/Renderer/D3D12/D3D12GrahicsDevice.h"
#include "SubSystem/Scene/Component/Components/Camera.h"
#include "SubSystem/Scene/Component/Components/RenderObject.h"

ForwardRenderer::ForwardRenderer()
{
	m_job.SetFunction([this](double) { Update(); }, FunctionType::Render);
	m_job.RegisterToJobSystem();
}

bool ForwardRenderer::Initialize()
{
	const auto width = Window::Get().GetWindowWidth();
	const auto height = Window::Get().GetWindowHeight();

	// デバイス初期化
	D3D11GraphicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());
	D3D12GraphicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());

	m_lightMap = MakeUnique<ForwardLightMap>();
	m_lightMap->Initialize();

	TransformCBuffer::Get().Init();

	EditerSystem::Get().Initialize();

	return true;
}

void ForwardRenderer::Shutdown()
{
	EditerSystem::Get().Exit();

	m_job.UnRegisterFromJobSystem();
}

void ForwardRenderer::Update() noexcept
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrix().ToMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrix().ToMatrixXM());

	//auto& grahicsDevice = D3D11GraphicsDevice::Get();
	//grahicsDevice.SetRenderTarget(grahicsDevice.GetRenderTarget(), grahicsDevice.GetDepthStencil());
	//grahicsDevice.Clear(Math::Vector4(0.8f, 0.8f, 0.8f, 1.f));

	D3D12GraphicsDevice::Get().Prepare(Math::Vector4(0.8f, 0.8f, 0.8f, 1.f));

	m_lightMap->Update(m_mainCamera);

	for (auto renderObject : m_renderObjects)
	{
		renderObject->Render();
	}

	EditerSystem::Get().Draw();

	//D3D11GraphicsDevice::Get().Present();
	D3D12GraphicsDevice::Get().Present();
}