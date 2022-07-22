/**
* @file	   GBuffer.cpp
* @brief
*
* @date	   2022/07/22 2022”N“x‰”Å
*/


#include "GBuffer.h"
#include "../D3D11/D3D11GrahicsDevice.h"
#include "../D3D12/D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

void GBuffer::Initialize(uint32_t wight, uint32_t height) noexcept
{
	m_rendererTexture[GBufferType::Color].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_rendererTexture[GBufferType::Normal].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_rendererTexture[GBufferType::Depth].Create(wight, height, DXGI_FORMAT_R32G32_FLOAT);
	m_rendererTexture[GBufferType::Parameter].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_rendererTexture12[GBufferType::Color].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_rendererTexture12[GBufferType::Normal].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_rendererTexture12[GBufferType::Depth].Create(wight, height, DXGI_FORMAT_R32G32_FLOAT);
	m_rendererTexture12[GBufferType::Parameter].Create(wight, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
}

void GBuffer::SetRenderTargets() const noexcept
{
	auto& grahicsDevice = D3D11GraphicsDevice::Get();

	ID3D11RenderTargetView* renderTargets[] = {
		m_rendererTexture[GBufferType::Color].GetRenderTarget(),
		m_rendererTexture[GBufferType::Normal].GetRenderTarget(),
		m_rendererTexture[GBufferType::Depth].GetRenderTarget(),
		m_rendererTexture[GBufferType::Parameter].GetRenderTarget(),
	};

	//CD3DX12_CPU_DESCRIPTOR_HANDLE handles[GBufferType::Max];
	//D3D12_CPU_DESCRIPTOR_HANDLE baseH = _peraRTVHeap->GetCPUDescriptorHandleForHeapStart();
	//auto incSize = _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//uint32_t offset = 0;
	//for (auto& handle : handles) {
	//	handle.InitOffsetted(baseH, offset);
	//	offset += incSize;
	//}

	//auto& grahicsDevice = D3D12GraphicsDevice::Get();



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