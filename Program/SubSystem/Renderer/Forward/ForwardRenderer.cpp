/**
* @file	   ForwardRenderer.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "ForwardRenderer.h"
#include "../LightMap.h"
#include "SubSystem/Gui/MyGui.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
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
	D3D11GrahicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());

	m_lightMap = MakeUnique<LightMap>();
	m_lightMap->Initialize();

	TransformCBuffer::Get().Init();

	MyGui::Get().Init();

	return true;
}

void ForwardRenderer::Shutdown()
{
	MyGui::Get().Exit();

	m_job.UnRegisterFromJobSystem();
}

void ForwardRenderer::Update() noexcept
{
	auto& grahicsDevice = D3D11GrahicsDevice::Get();

	grahicsDevice.SetRenderTarget(grahicsDevice.GetRenderTarget(), grahicsDevice.GetDepthStencil());
	grahicsDevice.Clear(Math::Vector4(0.8f, 0.8f, 0.8f, 1.f));

	m_lightMap->Update();

	for (auto renderObject : m_renderObjects)
	{
		renderObject->Render();
	}

	MyGui::Get().Draw();

	D3D11GrahicsDevice::Get().Present();
}