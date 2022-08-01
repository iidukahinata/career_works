/**
* @file    D3D12GrahicsDevice.cpp
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/


#include <array>
#include "D3D12GrahicsDevice.h"
#include "../directxtex/include/d3dx12.h"

#pragma comment(lib,"DirectXTex.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace std;
using namespace DirectX;

namespace {
	///�f�o�b�O���C���[��L���ɂ���
	void EnableDebugLayer() {
		ComPtr<ID3D12Debug> debugLayer = nullptr;
		auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
		debugLayer->EnableDebugLayer();
	}
}

bool D3D12GrahicsDevice::Init(HWND hwnd, UINT screenWidth, UINT screenHeight, bool isFullscreen)
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	EnableDebugLayer();
#endif

	if (!InitDevice()) {
		return false;
	}

	std::array<UINT, D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES> descriptorAllocSizes = { 1024, 128, 128, 32 };
	m_viewDescriptprAllocator.Initialize(descriptorAllocSizes[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV], D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_samplerDescriptprAllocator.Initialize(descriptorAllocSizes[D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER], D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
	m_rtvDescriptprAllocator.Initialize(descriptorAllocSizes[D3D12_DESCRIPTOR_HEAP_TYPE_RTV], D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_dsvDescriptprAllocator.Initialize(descriptorAllocSizes[D3D12_DESCRIPTOR_HEAP_TYPE_DSV], D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

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
	m_context.BegineFream();

	// �o�b�N�o�b�t�@�̃C���f�b�N�X���擾
	auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
	ResourceBarrier(m_renderTargets[bbIdx], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	D3D12RenderTextureView* renderTarges[] = {
		&m_renderTargetViews[bbIdx]
	};

	// �����_�[�^�[�Q�b�g���w��
	// �[�x���w��
	m_context.SetRenderTargets(1, renderTarges, &m_depthStencilView);

	// ��ʃN���A
	float clearColor[] = { 1.0f,0.0f,1.0f,1.0f };
	m_context.ClearRenderTargetView(&m_renderTargetViews[bbIdx], clearColor, 0, nullptr);
	m_context.ClearDepthStencilView(&m_depthStencilView, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// �r���[�|�[�g�A�V�U�[��`�̃Z�b�g
	m_context.SetViewPorts(1, &m_viewport);
	m_context.SetScissorRects(1, &m_scissorRect);
}

void D3D12GrahicsDevice::EndDraw() 
{
	auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
	ResourceBarrier(m_renderTargets[bbIdx], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_context.RunCommandList();

	WaitForGpuTask();

	m_context.Clear();
}

void D3D12GrahicsDevice::Present()
{
	m_swapchain->Present(1, 0);
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
	m_context.SetViewPorts(1, &viewport);
}

void D3D12GrahicsDevice::SetScissorRect(float width, float height)
{
	D3D12_RECT rect;
	rect.bottom = static_cast<LONG>(height);
	rect.top = 0;
	rect.left = 0;
	rect.right = static_cast<LONG>(width);
	m_context.SetScissorRects(1, &rect);
}

void D3D12GrahicsDevice::ResourceBarrier(ID3D12Resource* const pResource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState)
{
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(pResource, beforeState, afterState);
	m_context.GetCommandList()->ResourceBarrier(1, &transition);
}

void D3D12GrahicsDevice::WaitForGpuTask()
{
	// �҂�
	m_context.Signal(m_fence.Get(), m_fence.m_fenceValue);

	m_fence.WaitForSingleToFinish();
}

bool D3D12GrahicsDevice::InitDevice()
{
	// �@�\���x��
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

#ifdef _DEBUG
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_factory.ReleaseAndGetAddressOf()));
#else
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
#endif // _DEBUG
	if (FAILED(hr)) {
		return false;
	}

	IDXGIAdapter* adapter = GetAdapterByName(L"NVIDIA");
	if (!adapter)
	{
		return false;
	}

	// �w�肳�ꂽ�A�_�v�^�[�Ńf�o�C�X�̐���
	hr = S_FALSE;
	for (auto level : levels)
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

bool D3D12GrahicsDevice::CreateSwapChain(const HWND hwnd, UINT screenWidth, UINT screenHeight, UINT bufferCount)
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
	HRESULT hr = m_swapchain->GetDesc(&swcDesc);

	// SRGB�����_�[�^�[�Q�b�g�r���[�ݒ�
	m_renderTargets.resize(swcDesc.BufferCount);
	for (int i = 0; i < swcDesc.BufferCount; ++i) 
	{
		hr = m_swapchain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]));
		if (FAILED(hr)) {
			return false;
		}

		m_renderTargetViews[i].Create(m_renderTargets[i], m_renderTargets[i]->GetDesc().Format);
	}

	return true;
}

bool D3D12GrahicsDevice::CreateDepthStencil()
{
	DXGI_SWAP_CHAIN_DESC1 desc = {};
	auto hr = m_swapchain->GetDesc1(&desc);
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

	// DSV�p�q�[�v�v���p�e�B
	auto depthHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto depthClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

	hr = m_device->CreateCommittedResource(
		&depthHeapProp, D3D12_HEAP_FLAG_NONE,
		&resdesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(m_depthStencil.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	// �f�B�X�N���v�^���쐬
	m_depthStencilView.Create(m_depthStencil.Get());

	return true;
}

std::vector<IDXGIAdapter*> D3D12GrahicsDevice::GetAvailableAdapters()
{
	std::vector <IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	for (int i = 0; m_factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(adapter);
	}
	return adapters;
}

IDXGIAdapter* D3D12GrahicsDevice::GetAdapterByName(std::wstring_view name)
{
	std::vector <IDXGIAdapter*> adapters = GetAvailableAdapters();

	for (auto adpter : adapters)
	{
		DXGI_ADAPTER_DESC adesc = {};
		adpter->GetDesc(&adesc);

		std::wstring strDesc = adesc.Description;
		if (strDesc.find(name.data()) != std::string::npos) {
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