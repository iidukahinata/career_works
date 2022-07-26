/**
* @file    D3D12GrahicsDevice.h
* @brief
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include <dxgi1_6.h>
#include "D3D12CommandContext.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

class D3D12GrahicsDevice
{
	D3D12GrahicsDevice() = default;
	COPY_PROHIBITED(D3D12GrahicsDevice)
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
	void SetViewports(UINT numViewports, D3D12_VIEWPORT* viewports);
	void SetViewport(float width, float height);

	// ScissorRectangle
	void SetScissorRects(UINT numRects, D3D12_RECT* rects);
	void SetScissorRect(float width, float height);

	ID3D12Device*			   Device()		 const noexcept { return m_device.Get(); }
	ID3D12GraphicsCommandList* CommandList() const noexcept { return m_context.GetCommandList(); }
	IDXGISwapChain4*		   Swapchain()	 const noexcept { return m_swapchain.Get(); }

private:

	void ResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	bool InitDevice();
	bool CreateSwapChain(HWND hwnd, UINT screenWidth, UINT screenHeight, UINT bufferCount);
	bool CreateBackBuffer();
	bool CreateDepthStencil();

	Vector<IDXGIAdapter*> GetAvailableAdapters();
	IDXGIAdapter* GetAdapterByName(WstringView name);
	IDXGIAdapter* GetAdapterWithTheHighestVRAM();

private:

	Microsoft::WRL::ComPtr<IDXGIFactory4>			m_factory;

	// Direct3D objects
	Microsoft::WRL::ComPtr<ID3D12Device>			m_device;
	D3D12CommandContext								m_context;

	// swap chain objects
	Microsoft::WRL::ComPtr<IDXGISwapChain4>			m_swapchain;
	Vector<ID3D12Resource*>							m_renderTargets;
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_depthStencil;

	// fence object
	D3D12Fence										m_fence;

	// rendering objects
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_dsvDescriptorHeap;
	D3D12_VIEWPORT                                  m_viewport = {};
	D3D12_RECT                                      m_scissorRect = {};
};