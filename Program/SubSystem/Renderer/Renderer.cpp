/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/06/30 2022年度初版
*/


#include "Renderer.h"
#include "LightMap.h"
#include "GBuffer.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Gui/MyGui.h"
#include "ThirdParty/imgui/imgui.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "SubSystem/Scene/Component/Components/RenderObject.h"

Renderer::Renderer()
{
	m_job.SetFunction([this](double) { Update(); }, FunctionType::Render);
	m_job.RegisterToJobSystem();
}

bool Renderer::Initialize()
{
	auto width = Window::Get().GetWindowWidth();
	auto height = Window::Get().GetWindowHeight();

	// デバイス初期化
	D3D11GrahicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());

	// スクリーンサイズの四角形を作成
	m_quad.Create(width, height);

	// Set Up
	m_gbuffer = std::make_unique<GBuffer>();
	m_gbuffer->Initialize(width, height);

	m_lightMap = std::make_unique<LightMap>();
	m_lightMap->Initialize();

	// あとあといらない。
	TransformCBuffer::Get().Init();

	MyGui::Get().Init();

	return true;
}

void Renderer::Update() noexcept
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

void Renderer::FirstPass()
{
	m_gbuffer->SetRenderTargets();
	m_gbuffer->Clear();

	m_lightMap->Update();

	for (auto renderObject : m_renderObjects)
	{
		renderObject->Render();
	}
}

void Renderer::SecondPass()
{
	auto& grahicsDevice = D3D11GrahicsDevice::Get();

	grahicsDevice.SetRenderTarget(grahicsDevice.GetRenderTarget(), grahicsDevice.GetDepthStencil());
	grahicsDevice.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	m_quad.SetBuffer();

	const auto shaderResource = m_gbuffer->GetRenderTexture(GBufferType::Color).GetTexture()->GetAddressOfShaderResourceView();
	grahicsDevice.GetContext()->PSSetShaderResources(1, 1, shaderResource);
}

void Renderer::Shutdown()
{
	m_job.UnRegisterFromJobSystem();

	MyGui::Get().Exit();
}

void Renderer::RegisterRenderObject(RenderObject* rederObject) noexcept
{
	m_renderObjects.insert(rederObject);
}

void Renderer::RemoveRenderObject(RenderObject* rederObject) noexcept
{
	m_renderObjects.erase(rederObject);
}

void Renderer::AddLight(Light* light) noexcept
{
	m_lightMap->AddLight(light);
}

void Renderer::RemoveLight(Light* light) noexcept
{
	m_lightMap->RemoveLight(light);
}