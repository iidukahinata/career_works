/**
* @file    D3D12GrahicsDevice.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include "D3D12CommandContext.h"

class D3D12GraphicsDevice
{
	D3D12GraphicsDevice() = default;
	COPY_PROHIBITED(D3D12GraphicsDevice)
public:

	static D3D12GraphicsDevice& Get() noexcept
	{
		static D3D12GraphicsDevice instance;
		return instance;
	}

	// 初期化
	bool Init();

	// 更新
	void Prepare(const Math::Vector4& color);
	void Present();
	void WaitForGpu() noexcept;

	// ViewPort
	void SetViewports(UINT numViewports, const D3D12_VIEWPORT* viewports);
	void SetViewport(float width, float height);

	// ScissorRectangle
	void SetScissorRects(UINT numRects, const D3D12_RECT* rects);
	void SetScissorRect(float width, float height);

	ID3D12Device*		 GetDevice() const noexcept	  { return m_device.Get(); };
	D3D12CommandContext& GetCommandContext() noexcept { return m_commandContext; };

private:

	void ResourceBarrier(ID3D12Resource* const pResource, D3D12_RESOURCE_STATES stateBefore, D3D12_RESOURCE_STATES stateAfter);

	Vector<IDXGIAdapter*> GetAvailableAdapters(IDXGIFactory6* factory) const;
	IDXGIAdapter* GetAdapterWithTheHighestVRAM(IDXGIFactory6* factory) const;
	IDXGIAdapter* GetAdapterByName(const Wstring& adapterName, IDXGIFactory6* factory) const;

private:

	// Direct3D objects
	Microsoft::WRL::ComPtr<ID3D12Device>                m_device;
	D3D12CommandContext                                 m_commandContext;

	// swap chain objects
	Microsoft::WRL::ComPtr<IDXGISwapChain4>             m_swapchain;
	Vector<Microsoft::WRL::ComPtr<ID3D12Resource>>		m_renderTargets;
	Microsoft::WRL::ComPtr<ID3D12Resource>              m_depthStencil;

	// fence object
	D3D12Fence                                          m_fence;

	// rendering objects
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        m_rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        m_dsvDescriptorHeap;
	UINT                                                m_rtvDescriptorSize;
	D3D12_VIEWPORT                                      m_viewport = {};
	D3D12_RECT                                          m_scissorRect = {};
};