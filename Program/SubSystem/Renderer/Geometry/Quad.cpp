/**
* @file	   Quad.cpp
* @brief
*
* @date	   2022/07/01 2022îNìxèâî≈
*/



#include "Quad.h"

void Quad::Create(uint32_t width, uint32_t height) noexcept
{
	const Math::Vector2 halfSize(width / 2.f, height / 2.f);

	std::vector<Vertex2D> vertices(4);

	vertices[0].position = Math::Vector3( halfSize.x,  halfSize.y, 0.f);
	vertices[1].position = Math::Vector3(-halfSize.x,  halfSize.y, 0.f);
	vertices[2].position = Math::Vector3(-halfSize.x, -halfSize.y, 0.f);
	vertices[3].position = Math::Vector3( halfSize.x, -halfSize.y, 0.f);

	std::vector<UINT> indices = { 0, 1, 2, 2, 3, 0 };

	m_vertexBuffer.Create(vertices);
	m_indexBuffer.Create(indices);
}

void Quad::SetBuffer() noexcept
{
	m_vertexBuffer.IASet();
	m_indexBuffer.IASet();
}