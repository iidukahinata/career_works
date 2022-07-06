/**
* @file	   GBuffer.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "D3D11/D3D11RenderTexture.h"

enum GBufferType
{
	Color,
	Depth,
	Max,
};

class GBuffer
{
public:

	void Initialize(uint32_t wight, uint32_t height) noexcept;
	void SetRenderTargets() const noexcept;
	void Clear() noexcept;

	D3D11RenderTexture& GetRenderTexture(GBufferType type) noexcept;

private:

	Array<D3D11RenderTexture, GBufferType::Max> m_rendererTexture;
};