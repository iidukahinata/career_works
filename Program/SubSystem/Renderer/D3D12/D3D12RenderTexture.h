/**
* @file    D3D12RenderTexture.h
* @brief
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12RenderTexture : public D3D12DeviceChild
{
public:

	bool Create(UINT width, UINT height,
		DXGI_FORMAT colorFormat = DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT depthFormat = DXGI_FORMAT_D32_FLOAT) noexcept;

	/** デバイス設定するための関数です。*/
	void SetRenderTarget() const noexcept;

	/** 全ての要素を指定カラーに設定 */
	void Clear(const Math::Vector4& color) noexcept;

private:

	bool CreateRenderTarget(UINT width, UINT height, DXGI_FORMAT colorFormat) noexcept;
	bool CreateDepthStencil(UINT width, UINT height, DXGI_FORMAT depthFormat) noexcept;
	bool CreateDescriptorHeap() noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTarget;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_depthStencil;
	
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_dsvHeap;

	D3D12_VIEWPORT m_viewport = {};
};