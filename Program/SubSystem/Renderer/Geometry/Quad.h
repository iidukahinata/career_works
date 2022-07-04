/**
* @file	   Quad.h
* @brief
*
* @date	   2022/07/01 2022îNìxèâî≈
*/
#pragma once


#include "Vertex.h"
#include "../D3D11/D3D11VertexBuffer.h"
#include "../D3D11/D3D11IndexBuffer.h"

class Quad
{
public:

	void Create(uint32_t width, uint32_t height) noexcept;
	void SetBuffer() noexcept;
	uint32_t GetIndexCount() const { return 6; }

private:

	D3D11VertexBuffer<Vertex2D> m_vertexBuffer;
	D3D11IndexBuffer m_indexBuffer;
};