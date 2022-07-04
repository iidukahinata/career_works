/**
* @file	   GBuffer.h
* @brief
*
* @date	   2022/07/01 2022îNìxèâî≈
*/
#pragma once


#include <array>
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

	std::array<D3D11RenderTexture, GBufferType::Max> m_rendererTexture;
};