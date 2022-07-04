/**
* @file    Mesh.h
* @brief
*
* @date	   2022/07/01 2022�N�x����
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
	SUB_CLASS(Mesh)
public:

	Mesh() = default;
	void Construct(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices) noexcept;

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B*/
	void SaveToFile(std::string_view filePath) override;

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B*/
	bool LoadFromFile(std::string_view filePath) override;

	/** �A�N�Z�X */
	void SetVertices(const std::vector<VertexBump3D>& vertices) noexcept;
	const std::vector<VertexBump3D>& GetVertices() noexcept;

	void SetIndices(const std::vector<uint32_t>& indices) noexcept;
	const std::vector<uint32_t>& GetIndices() noexcept;

	void Render() const noexcept;

protected:

	virtual bool Do_Load(std::string_view filePath) override;

	std::string ConvertProprietaryFormat(std::string_view filePath) const noexcept;

private:

	bool SetUp() noexcept;

private:

	std::vector<VertexBump3D> m_vertices;
	std::vector<uint32_t> m_indices;

	D3D11VertexBuffer<VertexBump3D> m_vertexBuffer;
	D3D11IndexBuffer m_indexBuffer;
};