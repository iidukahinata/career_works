/**
* @file	   GBuffer.cpp
* @brief
*
* @date	   2022/07/07 2022îNìxèâî≈
*/


#include "GBuffer.h"
#include "../D3D11/D3D11GrahicsDevice.h"

void GBuffer::Initialize(uint32_t wight, uint32_t height) noexcept
{
	m_rendererTexture[GBufferType::Color].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_rendererTexture[GBufferType::Normal].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_rendererTexture[GBufferType::Depth].Create(wight, height, DXGI_FORMAT_R32G32_FLOAT);
	m_rendererTexture[GBufferType::Parameter].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
}

void GBuffer::SetRenderTargets() const noexcept
{
	auto& grahicsDevice = D3D11GrahicsDevice::Get();

	ID3D11RenderTargetView* renderTargets[] = {
		m_rendererTexture[GBufferType::Color].GetRenderTarget(),
		m_rendererTexture[GBufferType::Normal].GetRenderTarget(),
		m_rendererTexture[GBufferType::Depth].GetRenderTarget(),
		m_rendererTexture[GBufferType::Parameter].GetRenderTarget(),
	};

	grahicsDevice.SetRenderTargets(GBufferType::Max, renderTargets, m_rendererTexture[GBufferType::Color].GetDepthStencil());
}

void GBuffer::Clear() noexcept
{
	for (auto& renderTexture : m_rendererTexture)
	{
		renderTexture.Clear(Math::Vector4(0, 0, 0, 1));
	}
}

D3D11RenderTexture& GBuffer::GetRenderTexture(GBufferType type) noexcept
{
	return m_rendererTexture[type];
}