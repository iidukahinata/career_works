/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/


#include "Renderer.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Gui/MyGui.h"
#include "ThirdParty/imgui/imgui.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"

Renderer::Renderer()
{
	m_job.SetFunction([this](double) { Update(); });
	JobSystem::Get().RegisterJob(&m_job, FunctionType::Render);
}

bool Renderer::Initialize()
{
	D3D11GrahicsDevice::Get().Init();

	TransformCBuffer::Get().Init();

	MyGui::Get().Init();

	return true;
}

void Renderer::Update() noexcept
{
	BeginFream();

	// 実際の描画処理記述

	EndFream();
}

void Renderer::BeginFream()
{
	D3D11GrahicsDevice::Get().Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));
}

void Renderer::EndFream()
{
	MyGui::Get().Draw();

	D3D11GrahicsDevice::Get().Present();
}

void Renderer::Shutdown()
{
	JobSystem::Get().RemoveJob(&m_job);

	MyGui::Get().Exit();
}