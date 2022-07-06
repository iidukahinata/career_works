/**
* @file	   DeferredRenderer.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "DeferredRenderer.h"
#include "GBuffer.h"
#include "../LightMap.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "SubSystem/Scene/Component/Components/Camera.h"
#include "SubSystem/Scene/Component/Components/RenderObject.h"

bool DeferredRenderer::Initialize()
{
	const auto width = Window::Get().GetWindowWidth();
	const auto height = Window::Get().GetWindowHeight();

	if (Renderer::Initialize())
	{
		// スクリーンサイズの四角形を作成
		m_quad.Create(width, height);

		// Set Up
		m_gbuffer = MakeUnique<GBuffer>();
		m_gbuffer->Initialize(width, height);

		return true;
	}

	return false;
}

void DeferredRenderer::Update() noexcept
{
	FirstPass();

	Transform camera2D;
	camera2D.SetPosition(Math::Vector3(0, 0, -1));
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetOrthographicMatrixXM());
	TransformCBuffer::Get().SetView(camera2D.GetWorldMatrix().ToMatrixXM());

	SecondPass();

	FinalPass();
}

void DeferredRenderer::FirstPass() noexcept
{
	// GBuffer の生成
	m_gbuffer->SetRenderTargets();
	m_gbuffer->Clear();

	m_lightMap->Update();

	for (auto renderObject : m_renderObjects)
	{
		renderObject->Render();
	}
}

void DeferredRenderer::SecondPass() noexcept
{

}

void DeferredRenderer::FinalPass() noexcept
{
	auto& grahicsDevice = D3D11GrahicsDevice::Get();

	grahicsDevice.SetRenderTarget(grahicsDevice.GetRenderTarget(), grahicsDevice.GetDepthStencil());
	grahicsDevice.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	m_quad.SetBuffer();

	const auto shaderResource = m_gbuffer->GetRenderTexture(GBufferType::Color).GetTexture()->GetAddressOfShaderResourceView();
	grahicsDevice.GetContext()->PSSetShaderResources(1, 1, shaderResource);

	grahicsDevice.GetContext()->DrawIndexed(m_quad.GetIndexCount(), 0, 0);
}