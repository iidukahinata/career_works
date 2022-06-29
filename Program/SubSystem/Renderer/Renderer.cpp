/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/06/29 2022年度初版
*/


#include "Renderer.h"
#include "LightMap.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Gui/MyGui.h"
#include "ThirdParty/imgui/imgui.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "SubSystem/Scene/Component/Components/RenderObject.h"

Renderer::Renderer()
{
	m_job.SetFunction([this](double) { Update(); }, FunctionType::Render);
	JobSystem::Get().RegisterJob(&m_job);
}

bool Renderer::Initialize()
{
	D3D11GrahicsDevice::Get().Init();

	TransformCBuffer::Get().Init();

	m_lightMap = std::make_unique<LightMap>();
	m_lightMap->Initialize();

	MyGui::Get().Init();

	return true;
}

void Renderer::Update() noexcept
{
	BeginFream();

	// 実際の描画処理記述
	for (auto renderObject : m_renderObjects)
	{
		renderObject->Render();
	}

	EndFream();
}

void Renderer::BeginFream()
{
	D3D11GrahicsDevice::Get().Clear(Math::Vector4(0.8f, 0.8f, 0.8f, 1.f));

	m_lightMap->Update();
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

void Renderer::RegisterRenderObject(RenderObject* rederObject) noexcept
{
	m_renderObjects.emplace_back(rederObject);
}

void Renderer::RemoveRenderObject(RenderObject* rederObject) noexcept
{
	for (auto it = m_renderObjects.begin(); it != m_renderObjects.end(); it++)
	{
		if (*it == rederObject)
		{
			m_renderObjects.erase(it);
			break;
		}
	}
}

void Renderer::AddLight(Light* light) noexcept
{
	m_lightMap->AddLight(light);
}

void Renderer::RemoveLight(Light* light) noexcept
{
	m_lightMap->RemoveLight(light);
}