/**
* @file    D3D12RenderTexture.h
* @brief
*
* @date	   2022/08/01 2022年度初版
*/
#pragma once


#include <wrl/client.h>
#include "D3D12View.h"

class D3D12RenderTexture : public D3D12DeviceChild
{
public:

	bool Create(
		int width, int height,
		DXGI_FORMAT colorFormat = DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT depthFormat = DXGI_FORMAT_D32_FLOAT) noexcept;

	/** デバイス設定するための関数です。*/
	void SetRenderTarget() noexcept;

	/** 全ての要素を指定カラーに設定 */
	void Clear(float* color) noexcept;

private:

	bool CreateRenderTarget(int width, int height, DXGI_FORMAT colorFormat) noexcept;
	bool CreateDepthStencil(int width, int height, DXGI_FORMAT depthFormat) noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTarget;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_depthStencil;
	
	D3D12RenderTextureView m_renderTargetView;
	D3D12DepthStencilView m_depthStencilView;

	D3D12_VIEWPORT m_viewport = {};
};