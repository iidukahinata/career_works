/**
* @file    D3D12GrahicsDevice.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12GrahicsDevice::Init(HWND hwnd, UINT screenWidth, UINT screenHeight, bool isFullscreen)
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	Microsoft::WRL::ComPtr<ID3D12Debug> debugLayer = nullptr;
	auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
	debugLayer->EnableDebugLayer();
#endif

	if (!InitDevice()) {
		return false;
	}

	if (!m_context.Create()) {
		return false;
	}

	constexpr auto bufferCount = 2;
	if (!CreateSwapChain(hwnd, screenWidth, screenHeight, bufferCount)) {
		return false;
	}

	if (!CreateBackBuffer()) {
		return false;
	}

	if (!CreateDepthStencil()) {
		return false;
	}

	if (!m_fence.Create()) {
		return false;
	}

	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.Width = screenWidth;
	m_viewport.Height = screenHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	m_scissorRect.bottom = static_cast<LONG>(screenHeight);
	m_scissorRect.top = 0;
	m_scissorRect.left = 0;
	m_scissorRect.right = static_cast<LONG>(screenWidth);

	return true;
}

void D3D12GrahicsDevice::BeginDraw() 
{
	// バックバッファのインデックスを取得
	const auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
	ResourceBarrier(m_renderTargets[bbIdx], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	// レンダーターゲットを指定
	auto rtvH = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	rtvH.ptr += bbIdx * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// 深度を指定
	const auto dsvH = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_context.GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	// 画面クリア
	const float clearColor[] = { 1.0f,0.0f,1.0f,1.0f };//白色
	m_context.GetCommandList()->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	m_context.GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// ビューポート、シザー矩形のセット
	SetViewports(1, &m_viewport);
	SetScissorRects(1, &m_scissorRect);
}

void D3D12GrahicsDevice::EndDraw() 
{
	const auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
	ResourceBarrier(m_renderTargets[bbIdx], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_context.RunCommandList();

	WaitForGpuTask();

	m_context.Clear();
}

void D3D12GrahicsDevice::Present()
{
	m_swapchain->Present(1, 0);
}

void D3D12GrahicsDevice::SetViewports(UINT numViewports, D3D12_VIEWPORT* viewports)
{
	m_context.GetCommandList()->RSSetViewports(numViewports, viewports);
}

void D3D12GrahicsDevice::SetViewport(float width, float height)
{
	D3D12_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	SetViewports(1, &viewport);
}

void D3D12GrahicsDevice::SetScissorRects(UINT numRects, D3D12_RECT* rects)
{
	m_context.GetCommandList()->RSSetScissorRects(numRects, rects);
}

void D3D12GrahicsDevice::SetScissorRect(float width, float height)
{
	D3D12_RECT rect;
	rect.bottom = static_cast<LONG>(height);
	rect.top = 0;
	rect.left = 0;
	rect.right = static_cast<LONG>(width);
	SetScissorRects(1, &rect);
}

void D3D12GrahicsDevice::ResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState)
{
	const auto transition = CD3DX12_RESOURCE_BARRIER::Transition(resource, beforeState, afterState);
	m_context.GetCommandList()->ResourceBarrier(1, &transition);
}

void D3D12GrahicsDevice::WaitForGpuTask()
{
	// 待ち
	m_context.Signal(m_fence.Get(), m_fence.m_fenceValue);

	m_fence.WaitForSingleToFinish();
}

bool D3D12GrahicsDevice::InitDevice()
{
	// 機能レベル
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

#ifdef _DEBUG
	auto hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_factory.ReleaseAndGetAddressOf()));
#else
	auto hr = CreateDXGIFactory1(IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
#endif // _DEBUG
	if (FAILED(hr)) {
		return false;
	}

	const auto adapter = GetAdapterByName(L"NVIDIA");
	if (!adapter)
	{
		return false;
	}

	// 指定されたアダプターでデバイスの生成
	hr = S_FALSE;
	for (const auto& level : levels)
	{
		hr = D3D12CreateDevice(adapter, level, IID_PPV_ARGS(m_device.ReleaseAndGetAddressOf()));
		if (SUCCEEDED(hr)) {
			break;
		}
	}

	if (FAILED(hr)) {
		return false;
	}

	return true;
}

bool D3D12GrahicsDevice::CreateSwapChain(HWND hwnd, UINT screenWidth, UINT screenHeight, UINT bufferCount)
{
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width = screenWidth;
	swapchainDesc.Height = screenHeight;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount = bufferCount;
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	auto result = m_factory->CreateSwapChainForHwnd(
		m_context.GetCommandQueue(),
		hwnd,
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)m_swapchain.ReleaseAndGetAddressOf());

	if (FAILED(result)) {
		return false;
	}

	return true;
}

bool D3D12GrahicsDevice::CreateBackBuffer()
{
	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	auto hr = m_swapchain->GetDesc(&swcDesc);

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = swcDesc.BufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	hr = m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(m_rtvDescriptorHeap.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	auto handle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	// SRGBレンダーターゲットビュー設定
	m_renderTargets.resize(swcDesc.BufferCount);
	for (int i = 0; i < swcDesc.BufferCount; ++i) {
		hr = m_swapchain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]));
		if (FAILED(hr)) {
			return false;
		}

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = m_renderTargets[i]->GetDesc().Format;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		m_device->CreateRenderTargetView(m_renderTargets[i], &rtvDesc, handle);

		handle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	return true;
}

bool D3D12GrahicsDevice::CreateDepthStencil()
{
	// DSV用のディスクリプタヒープを作成する。
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	auto hr = m_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_dsvDescriptorHeap.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	DXGI_SWAP_CHAIN_DESC1 desc = {};
	hr = m_swapchain->GetDesc1(&desc);
	if (FAILED(hr)) {
		return false;
	}

	CD3DX12_RESOURCE_DESC resdesc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		desc.Width,
		desc.Height,
		1,
		1,
		DXGI_FORMAT_D32_FLOAT,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

	// DSV用ヒーププロパティ
	const auto depthHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	const auto depthClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

	hr = m_device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&resdesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(m_depthStencil.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	// ディスクリプタを作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	m_device->CreateDepthStencilView(m_depthStencil.Get(), &dsvDesc, m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	return true;
}

std::vector<IDXGIAdapter*> D3D12GrahicsDevice::GetAvailableAdapters()
{
	Vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	for (int i = 0; m_factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(adapter);
	}
	return adapters;
}

IDXGIAdapter* D3D12GrahicsDevice::GetAdapterByName(WstringView name)
{
	const auto adapters = GetAvailableAdapters();

	for (const auto adpter : adapters)
	{
		DXGI_ADAPTER_DESC adesc = {};
		adpter->GetDesc(&adesc);

		WstringView strDesc = adesc.Description;
		if (strDesc.find(name.data()) != String::npos) {
			return adpter;
		}
	}
	return nullptr;
}

IDXGIAdapter* D3D12GrahicsDevice::GetAdapterWithTheHighestVRAM()
{
	auto adapters = GetAvailableAdapters();

	IDXGIAdapter* resultAdapter = nullptr;
	UINT maxVRAMSize = 0;

	DXGI_ADAPTER_DESC adesc = {};
	for (auto adapter : adapters)
	{
		adapter->GetDesc(&adesc);
		if (adesc.DedicatedVideoMemory > maxVRAMSize)
		{
			maxVRAMSize = adesc.DedicatedVideoMemory;
			resultAdapter = adapter;
		}
	}

	return resultAdapter;
}