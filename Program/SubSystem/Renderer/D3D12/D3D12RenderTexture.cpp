/**
* @file    D3D12RenderTexture.cpp
* @brief
*
* @date	   2022/07/30 2022”N“x‰”Å
*/


#include "D3D12RenderTexture.h"
#include "D3D12GrahicsDevice.h"
#include "../directxtex/include/d3dx12.h"

bool D3D12RenderTexture::Create(int width, int height, DXGI_FORMAT colorFormat, DXGI_FORMAT depthFormat) noexcept
{
	if (!CreateRenderTarget(width, height, colorFormat))
		return false;

	if (!CreateDepthStencil(width, height, depthFormat))
		return false;

	m_renderTargetView.Create(m_renderTarget.Get(), m_renderTarget.Get()->GetDesc().Format);
	m_depthStencilView.Create(m_depthStencil.Get());

	return true;
}

void D3D12RenderTexture::SetRenderTarget() noexcept
{
	D3D12RenderTextureView* renderTargets[] = {
		&m_renderTargetView
	};

	GetCommandContext()->SetRenderTargets(1, renderTargets, &m_depthStencilView);
	GetCommandContext()->SetViewPorts(1, &m_viewport);
}

void D3D12RenderTexture::Clear(float* color) noexcept
{
	float clearColor[] = { color[0], color[1], color[2], color[3] };
	GetCommandContext()->GetCommandList()->ClearRenderTargetView(m_renderTargetView.GetCPUHandle(), clearColor, 0, nullptr);
	GetCommandContext()->GetCommandList()->ClearDepthStencilView(m_depthStencilView.GetCPUHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

bool D3D12RenderTexture::CreateRenderTarget(int width, int height, DXGI_FORMAT colorFormat) noexcept
{
	CD3DX12_RESOURCE_DESC renderTargetDesc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(width),
		static_cast<UINT>(height),
		1,
		1,
		colorFormat,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

	D3D12_CLEAR_VALUE rtvClearValue;
	rtvClearValue.Format = colorFormat;
	rtvClearValue.Color[0] = 0.f;
	rtvClearValue.Color[1] = 0.f;
	rtvClearValue.Color[2] = 0.f;
	rtvClearValue.Color[3] = 1.f;

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	HRESULT hr = GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&renderTargetDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&rtvClearValue,
		IID_PPV_ARGS(m_renderTarget.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}
	return true;
}

bool D3D12RenderTexture::CreateDepthStencil(int width, int height, DXGI_FORMAT depthFormat) noexcept
{
	CD3DX12_RESOURCE_DESC depthStencilDesc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(width),
		static_cast<UINT>(height),
		1,
		1,
		depthFormat,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

	D3D12_CLEAR_VALUE dsvClearValue = {};
	dsvClearValue.Format = depthFormat;
	dsvClearValue.DepthStencil.Depth = 1.0f;
	dsvClearValue.DepthStencil.Stencil = 0;

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	HRESULT hr = GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&dsvClearValue,
		IID_PPV_ARGS(m_depthStencil.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}
	return true;
}