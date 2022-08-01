/**
* @file    D3D12GrahicsDevice.h
* @brief
*
* @date	   2022/08/01 2022年度初版
*/
#pragma once


#include <dxgi1_6.h>
#include "D3D12View.h"
#include "D3D12Helper.h"
#include "D3D12CommandContext.h"
#include "D3D12DescriptorAllocator.h"
#include "../directxtex/include/DirectXTex.h"

class D3D12Sampler;

class D3D12GrahicsDevice
{
	D3D12GrahicsDevice() = default;
public:

	static D3D12GrahicsDevice& Get() noexcept
	{
		static D3D12GrahicsDevice instance;
		return instance;
	}

	// 初期化
	bool Init(HWND hwnd, UINT screenWidth, UINT screenHeight, bool isFullscreen);

	// 更新
	void BeginDraw();
	void EndDraw();
	void Present();
	void WaitForGpuTask();

	// ViewPort
	void SetViewport(float width, float height);

	// ScissorRect
	void SetScissorRect(float width, float height);

	/** アクセス */
	ID3D12Device*			   Device()						const noexcept { return m_device.Get(); }
	D3D12CommandContext&       CommandContext()					  noexcept { return m_context; }
	IDXGISwapChain4*		   Swapchain()					const noexcept { return m_swapchain.Get(); }
	D3D12DescriptorAllocator&  ViewDescriptorAllocator()		  noexcept { return m_viewDescriptprAllocator; }
	D3D12DescriptorAllocator&  SamplerDescriptorAllocator()		  noexcept { return m_samplerDescriptprAllocator; }
	D3D12DescriptorAllocator&  RtvDescriptorAllocator()			  noexcept { return m_rtvDescriptprAllocator; }
	D3D12DescriptorAllocator&  DsvDescriptorAllocator()			  noexcept { return m_dsvDescriptprAllocator; }
	D3D12Map<D3D12_SAMPLER_DESC, D3D12Sampler*>& GetSamplerMap()  noexcept { return m_samplerMap; }

private:

	void ResourceBarrier(ID3D12Resource* const pResource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	bool InitDevice();
	bool CreateSwapChain(const HWND hwnd, UINT screenWidth, UINT screenHeight, UINT bufferCount);
	bool CreateBackBuffer();
	bool CreateDepthStencil();

	std::vector<IDXGIAdapter*> GetAvailableAdapters();
	IDXGIAdapter* GetAdapterByName(std::wstring_view name);
	IDXGIAdapter* GetAdapterWithTheHighestVRAM();

private:

	Microsoft::WRL::ComPtr <IDXGIFactory4>			m_factory;

	// * Direct3D objects
	Microsoft::WRL::ComPtr<ID3D12Device>			m_device;
	D3D12CommandContext								m_context;

	// * swap chain objects
	Microsoft::WRL::ComPtr<IDXGISwapChain4>			m_swapchain;
	std::vector<ID3D12Resource*>					m_renderTargets;
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_depthStencil;

	// * fence object
	D3D12Fence										m_fence;

	// * rendering objects
	D3D12RenderTextureView							m_renderTargetViews[2];
	D3D12DepthStencilView							m_depthStencilView;
	D3D12_VIEWPORT                                  m_viewport = {};
	D3D12_RECT                                      m_scissorRect = {};

	// * allocator objects
	D3D12DescriptorAllocator						m_viewDescriptprAllocator;
	D3D12DescriptorAllocator						m_samplerDescriptprAllocator;
	D3D12DescriptorAllocator						m_rtvDescriptprAllocator;
	D3D12DescriptorAllocator						m_dsvDescriptprAllocator;

	D3D12Map<D3D12_SAMPLER_DESC, D3D12Sampler*>		m_samplerMap;
};