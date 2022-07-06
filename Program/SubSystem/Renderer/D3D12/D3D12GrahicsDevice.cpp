/**
* @file    D3D12GrahicsDevice.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "D3D12GrahicsDevice.h"
#include "SubSystem/Window/Window.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12GrahicsDevice::Init()
{
	auto hWnd = Window::Get().GetHandle();

	auto screenWidth = Window::Get().GetWindowWidth();
	auto screenHeight = Window::Get().GetWindowHeight();
	constexpr auto bufferCount = 2;

	//機能レベル
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
	};

	Microsoft::WRL::ComPtr<IDXGIFactory6> factory;

#ifdef _DEBUG
	// エラーメッセージの取得を行えるようにする
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
#else
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
#endif // _DEBUG
	if (FAILED(hr)) {
		return false;
	}

	// VROMが最大のアダプターを取得
	IDXGIAdapter* adapter = GetAdapterWithTheHighestVRAM(factory.Get());
	if (!adapter) {
		return false;
	}

	// 指定されたアダプターでデバイスの生成
	for (auto level : levels)
	{
		hr = D3D12CreateDevice(adapter, level, IID_PPV_ARGS(m_device.ReleaseAndGetAddressOf()));
		if (SUCCEEDED(hr)) {
			break;
		}
	}

	adapter->Release();

	if (FAILED(hr)) {
		return false;
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = bufferCount;
	swapChainDesc.Width = screenWidth;
	swapChainDesc.Height = screenHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	IDXGISwapChain1* swapchain;
	hr = factory->CreateSwapChainForHwnd(
		m_commandContext.GetCommandQueue(),
		hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapchain);

	if (FAILED(hr)) {
		return false;
	}

	//IDXGISwapChain4のインターフェースを取得。
	hr = swapchain->QueryInterface(IID_PPV_ARGS(m_swapchain.ReleaseAndGetAddressOf()));
	swapchain->Release();
	if (FAILED(hr)) {
		return false;
	}

	//RTV用のディスクリプタヒープを作成する。
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = bufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(m_rtvDescriptorHeap.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	//フロントバッファをバックバッファ用のRTVを作成。
	m_renderTargets.resize(bufferCount);
	for (int i = 0; i < bufferCount; ++i) {
		m_swapchain->GetBuffer(i, IID_PPV_ARGS(m_renderTargets[i].ReleaseAndGetAddressOf()));
		m_device->CreateRenderTargetView(m_renderTargets[i].Get(), nullptr, rtvHandle);

		// ディスクリプタのサイズ加算
		rtvHandle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	//DSV用のディスクリプタヒープを作成する。
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = m_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_dsvDescriptorHeap.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	D3D12_CLEAR_VALUE dsvClearValue;
	dsvClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	dsvClearValue.DepthStencil.Depth = 1.0f;
	dsvClearValue.DepthStencil.Stencil = 0;

	CD3DX12_RESOURCE_DESC resourceDesc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		screenWidth,
		screenHeight,
		1,
		1,
		DXGI_FORMAT_D32_FLOAT,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	hr = m_device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&dsvClearValue,
		IID_PPV_ARGS(m_depthStencil.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	//ディスクリプタを作成
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_device->CreateDepthStencilView(m_depthStencil.Get(), nullptr, dsvHandle);

	// viewport 初期化
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.Width = screenWidth;
	m_viewport.Height = screenHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	// rect 初期化
	m_scissorRect.bottom = static_cast<LONG>(screenHeight);
	m_scissorRect.top = 0;
	m_scissorRect.left = 0;
	m_scissorRect.right = static_cast<LONG>(screenWidth);

	return false;
}

void D3D12GrahicsDevice::Prepare(const Math::Vector4& color)
{
	m_commandContext.Clear();

	// バックバッファに描画出来る状態に遷移させる
	ResourceBarrier(
		m_renderTargets[0].Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	//SetViewports(1, &m_viewport);
	//SetScissorRect(m_viewport.Width, m_viewport.Height);

	// レンダーターゲットクリア
}

void D3D12GrahicsDevice::Present()
{
	// 画面に表示出来る状態に遷移させる
	ResourceBarrier(
		m_renderTargets[0].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);

	// コミット？

	// コマンドリストをGPUに送信して実行させる
	m_commandContext.RunCommandList();

	m_swapchain->Present(1, 0);

	WaitForGpu();
}

void D3D12GrahicsDevice::WaitForGpu() noexcept
{
	m_commandContext.Signal(m_fence.Get(), m_fence.m_fenceValue);

	m_fence.WaitForSingleToFinish();
}

void D3D12GrahicsDevice::SetViewports(UINT numViewports, const D3D12_VIEWPORT* viewports)
{
	m_commandContext.GetCommandList()->RSSetViewports(numViewports, viewports);
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

void D3D12GrahicsDevice::SetScissorRects(UINT numRects, const D3D12_RECT* rects)
{
	m_commandContext.GetCommandList()->RSSetScissorRects(numRects, rects);
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

void D3D12GrahicsDevice::ResourceBarrier(ID3D12Resource* const pResource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState)
{
	auto&& barriers = CD3DX12_RESOURCE_BARRIER::Transition(pResource, beforeState, afterState);
	m_commandContext.GetCommandList()->ResourceBarrier(1, &barriers);
}

Vector<IDXGIAdapter*> D3D12GrahicsDevice::GetAvailableAdapters(IDXGIFactory6* factory) const
{
	Vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	for (int i = 0; factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(adapter);
	}
	return adapters;
}

IDXGIAdapter* D3D12GrahicsDevice::GetAdapterWithTheHighestVRAM(IDXGIFactory6* factory) const
{
	auto adapters = GetAvailableAdapters(factory);

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

	// 使わないアダプターを解放
	for (auto adapter : adapters)
	{
		if (resultAdapter != adapter) {
			adapter->Release();
		}
	}
	return resultAdapter;
}

IDXGIAdapter* D3D12GrahicsDevice::GetAdapterByName(const Wstring& adapterName, IDXGIFactory6* factory) const
{
	Vector<IDXGIAdapter*> adapters = GetAvailableAdapters(factory);

	DXGI_ADAPTER_DESC adesc = {};
	for (auto adapter : adapters)
	{
		adapter->GetDesc(&adesc);
		Wstring strDesc(adesc.Description);

		if (strDesc.find(adapterName.data()) != String::npos)
		{
			return adapter;
		}
	}
	return nullptr;
}