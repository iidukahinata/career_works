/**
* @file    Mesh.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include <span>
#include <vector>
#include "../IResource.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"

class Mesh : public IResource
{
public:

	Mesh() = default;
	Mesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices);
	Mesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices);

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B */
	virtual void SaveToFile(std::string_view filePath) override;

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B */
	virtual bool LoadFromFile(std::string_view filePath) override;

	/** �A�N�Z�X */
	std::span<VertexBump3D> GetVertices() noexcept;
	std::span<uint32_t> GetIndices() noexcept;

protected:

	virtual bool Do_Load(std::string_view filePath) override;

private:

	std::vector<VertexBump3D> m_vertices;
	std::vector<uint32_t> m_indices;
};