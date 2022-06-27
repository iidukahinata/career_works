/**
* @file    Mesh.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include <span>
#include <vector>
#include "../IResource.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Renderer/D3D11/D3D11IndexBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11VertexBuffer.h"

class Mesh : public IResource
{
public:

	Mesh() = default;
	Mesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices);
	Mesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices);

	/** アクセス */
	const std::vector<VertexBump3D>& GetVertices() noexcept;
	const std::vector<uint32_t>& GetIndices() noexcept;

	void Render() const noexcept;

protected:

	virtual bool Do_Load(std::string_view filePath) override;

private:

	bool SetUp() noexcept;

private:

	std::vector<VertexBump3D> m_vertices;
	std::vector<uint32_t> m_indices;

	D3D11VertexBuffer<VertexBump3D> m_vertexBuffer;
	D3D11IndexBuffer m_indexBuffer;
};