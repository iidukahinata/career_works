/**
* @file    Mesh.cpp
* @brief
*
* @date	   2022/06/25 2022îNìxèâî≈
*/


#include "Mesh.h"

Mesh::Mesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices) : m_vertices(vertices), m_indices(indices)
{

}

Mesh::Mesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices) : m_vertices(vertices), m_indices(indices)
{

}

void Mesh::SaveToFile(std::string_view filePath)
{
}

bool Mesh::LoadFromFile(std::string_view filePath)
{
	return false;
}

std::span<VertexBump3D> Mesh::GetVertices() noexcept
{
	return m_vertices;
}

std::span<uint32_t> Mesh::GetIndices() noexcept
{
	return m_indices;
}

bool Mesh::Do_Load(std::string_view filePath)
{
	return false;
}