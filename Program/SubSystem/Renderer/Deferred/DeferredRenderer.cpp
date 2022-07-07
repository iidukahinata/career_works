/**
* @file	   DeferredRenderer.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "DeferredRenderer.h"
#include "SubSystem/Gui/MyGui.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "SubSystem/Scene/Component/Components/Camera.h"
#include "SubSystem/Scene/Component/Components/RenderObject.h"

DeferredRenderer::DeferredRenderer()
{
	m_job.SetFunction([this](double) { Update(); }, FunctionType::Render);
	m_job.RegisterToJobSystem();
}

bool DeferredRenderer::Initialize()
{
	const auto width = Window::Get().GetWindowWidth();
	const auto height = Window::Get().GetWindowHeight();

	// デバイス初期化
	D3D11GrahicsDevice::Get().Init(Window::Get().GetHandle(), width, height, Window::Get().IsFullscreen());

	// Set Up
	m_gbuffer = MakeUnique<GBuffer>();
	m_gbuffer->Initialize(width, height);

	m_lightMap = MakeUnique<LightMap>();
	m_lightMap->Initialize();

	TransformCBuffer::Get().Init();

	MyGui::Get().Init();

	// スクリーンサイズの四角形を作成
	m_quad.Create(width, height);

	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0							, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_vsShader.Create("assets/Resource/Shader/TextureVS.cso");
	m_inputLayout.Create(inputLayout, ARRAYSIZE(inputLayout), m_vsShader.GetBlob());

	m_psShader.Create("assets/Resource/Shader/TexturePS.cso");
	m_samplerState.Create();
	
	return true;
}

void DeferredRenderer::Shutdown()
{
	MyGui::Get().Exit();

	m_job.UnRegisterFromJobSystem();
}

void DeferredRenderer::Update() noexcept
{
	if (!m_mainCamera)
		return;

	GBufferPass();

	// ここから下の描画処理は2D処理のみ
	Set2DCamera();

	LightingPass();

	FinalPass();

	MyGui::Get().Draw();

	D3D11GrahicsDevice::Get().Present();
}

void DeferredRenderer::GBufferPass() const noexcept
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrix().ToMatrixXM());

	// GBuffer の生成
	m_gbuffer->SetRenderTargets();
	m_gbuffer->Clear();
	
	m_lightMap->Update();

	// 通常描画
	for (auto renderObject : m_renderObjects)
	{
		renderObject->Render();
	}
}

void DeferredRenderer::LightingPass() const noexcept
{

}

void DeferredRenderer::FinalPass() noexcept
{
	auto& grahicsDevice = D3D11GrahicsDevice::Get();
	
	// メインバッファーをセット
	grahicsDevice.SetRenderTarget(grahicsDevice.GetRenderTarget(), grahicsDevice.GetDepthStencil());
	grahicsDevice.Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));

	// シェーダーセット
	m_vsShader.VSSet();
	m_psShader.PSSet();
	m_samplerState.PSSet();

	// 頂点レイアウトをセット
	m_inputLayout.IASet();

	// プリミティブタイプをセット
	D3D11GrahicsDevice::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// テクスチャをセット
	m_gbuffer->GetRenderTexture(GBufferType::Color).GetTexture()->PSSet();

	// 頂点バッファーをセット
	m_quad.SetBuffer();

	grahicsDevice.GetContext()->DrawIndexed(m_quad.GetIndexCount(), 0, 0);
}

void DeferredRenderer::Set2DCamera() const noexcept
{
	Transform camera2D(Math::Vector3(0, 0, 1));
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetOrthographicMatrixXM());
	TransformCBuffer::Get().SetView(camera2D.GetWorldMatrix().ToMatrixXM());
	TransformCBuffer::Get().Bind(Math::Matrix::Identity.ToMatrixXM());
}