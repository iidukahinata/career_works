/**
* @file    Mesh.cpp
* @brief
*
* @date	   2022/06/25 2022年度初版
*/


#include "Mesh.h"

Mesh::Mesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices) : m_vertices(vertices), m_indices(indices)
{
	SetUp();
}

Mesh::Mesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices) : m_vertices(vertices), m_indices(indices)
{
	SetUp();
}

const std::vector<VertexBump3D>& Mesh::GetVertices() noexcept
{
	return m_vertices;
}

const std::vector<uint32_t>& Mesh::GetIndices() noexcept
{
	return m_indices;
}

void Mesh::Render() const noexcept
{
	// 頂点バッファのパラメータセット
	m_vertexBuffer.IASet();

	// インデックスバッファのパラメータセット
	m_indexBuffer.IASet();

	// プリミティブタイプをセット
	auto context = m_vertexBuffer.GetContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Mesh::Do_Load(std::string_view filePath)
{
	return false;
}

bool Mesh::SetUp() noexcept
{
	// CPU側からの更新はないものとして D3D11_USAGE_DEFAULT で生成。
	if (!m_vertexBuffer.Create(m_vertices))
	{
		return false;
	}

	// CPU側からの更新はないものとして D3D11_USAGE_DEFAULT で生成。
	if (!m_indexBuffer.Create(m_indices))
	{
		return false;
	}
	return true;
}