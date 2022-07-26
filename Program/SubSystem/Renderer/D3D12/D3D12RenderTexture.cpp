/**
* @file    D3D12RenderTexture.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "D3D12RenderTexture.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12RenderTexture::Create(UINT width, UINT height, DXGI_FORMAT colorFormat, DXGI_FORMAT depthFormat) noexcept
{
	if (!CreateRenderTarget(width, height, colorFormat))
		return false;

	if (!CreateDepthStencil(width, height, depthFormat))
		return false;

	if (!CreateDescriptorHeap())
		return false;

	// レンダーターゲットテクスチャのディスクリプタを作成
	const auto rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	GetDevice()->CreateRenderTargetView(m_renderTarget.Get(), nullptr, rtvHandle);

	// 深度テクスチャのディスクリプタを作成
	const auto dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
	GetDevice()->CreateDepthStencilView(m_depthStencil.Get(), nullptr, dsvHandle);

	return true;
}

void D3D12RenderTexture::SetRenderTarget() const noexcept
{
	const auto rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	const auto dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();

	GetCommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
}

void D3D12RenderTexture::Clear(const Math::Vector4& color) noexcept
{
	const auto rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	const auto dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();

	const float clearColor[] = { color.x, color.y, color.z, color.w };
	GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	GetCommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	GetCommandList()->RSSetViewports(1, &m_viewport);
}

bool D3D12RenderTexture::CreateRenderTarget(UINT width, UINT height, DXGI_FORMAT colorFormat) noexcept
{
	CD3DX12_RESOURCE_DESC renderTargetDesc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<const UINT>(width),
		static_cast<const UINT>(height),
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

	const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	auto hr = GetDevice()->CreateCommittedResource(
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

bool D3D12RenderTexture::CreateDepthStencil(UINT width, UINT height, DXGI_FORMAT depthFormat) noexcept
{
	CD3DX12_RESOURCE_DESC depthStencilDesc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<const UINT>(width),
		static_cast<const UINT>(height),
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

	const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	auto hr = GetDevice()->CreateCommittedResource(
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

bool D3D12RenderTexture::CreateDescriptorHeap() noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC descriptorDesc = {};
	descriptorDesc.NumDescriptors = 2;
	descriptorDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	descriptorDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	auto hr = GetDevice()->CreateDescriptorHeap(&descriptorDesc, IID_PPV_ARGS(m_rtvHeap.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	descriptorDesc.NumDescriptors = 1;
	descriptorDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	hr = GetDevice()->CreateDescriptorHeap(&descriptorDesc, IID_PPV_ARGS(m_dsvHeap.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}
	return true;
}