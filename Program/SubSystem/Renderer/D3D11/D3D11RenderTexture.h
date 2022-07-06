/**
* @file    D3D11RenderTexture.h
* @brief   
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "D3D11DeviceChild.h"
#include "D3D11Texture.h"

class D3D11RenderTexture : public D3D11DeviceChild
{
public:

	bool Create(
		UINT widthSize,
		UINT heightSize,
		DXGI_FORMAT colorFormat = DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT depthFormat = DXGI_FORMAT_D32_FLOAT) noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void SetRenderTarget() noexcept;

	/** �S�Ă̗v�f���w��J���[�ɐݒ� */
	void Clear(Math::Vector4 color) noexcept;

	/* �A�N�Z�X */
	ID3D11RenderTargetView* GetRenderTarget() const noexcept { return m_renderTarget.Get(); };
	ID3D11DepthStencilView* GetDepthStencil() const noexcept { return m_depthStencil.Get(); };
	D3D11Texture*           GetTexture() noexcept            { return &m_texture; };

private:

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencil;
	D3D11Texture m_texture;

	D3D11_VIEWPORT m_viewport = {};
};