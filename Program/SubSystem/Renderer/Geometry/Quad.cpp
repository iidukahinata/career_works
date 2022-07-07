/**
* @file	   Quad.cpp
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/



#include "Quad.h"

void Quad::Create(float width, float height) noexcept
{
	const Math::Vector2 halfSize(width / 2.f, height / 2.f);

	Vector<Vertex3D> vertices(4);

	vertices[0].position = Math::Vector3( halfSize.x,  halfSize.y, 0.f);
	vertices[1].position = Math::Vector3(-halfSize.x,  halfSize.y, 0.f);
	vertices[2].position = Math::Vector3(-halfSize.x, -halfSize.y, 0.f);
	vertices[3].position = Math::Vector3( halfSize.x, -halfSize.y, 0.f);

	vertices[0].tex = Math::Vector2(1, 0);
	vertices[1].tex = Math::Vector2(0, 0);
	vertices[2].tex = Math::Vector2(0, 1);
	vertices[3].tex = Math::Vector2(1, 1);

	Vector<UINT> indices = { 0, 1, 2, 2, 3, 0 };

	m_vertexBuffer.Create(vertices);
	m_indexBuffer.Create(indices);
}

void Quad::SetBuffer() noexcept
{
	m_vertexBuffer.IASet();
	m_indexBuffer.IASet();
}