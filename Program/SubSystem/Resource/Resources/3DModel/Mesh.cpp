/**
* @file    Mesh.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
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
	// ���_�o�b�t�@�̃p�����[�^�Z�b�g
	m_vertexBuffer.IASet();

	// �C���f�b�N�X�o�b�t�@�̃p�����[�^�Z�b�g
	m_indexBuffer.IASet();

	// �v���~�e�B�u�^�C�v���Z�b�g
	auto context = m_vertexBuffer.GetContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Mesh::Do_Load(std::string_view filePath)
{
	return false;
}

bool Mesh::SetUp() noexcept
{
	// CPU������̍X�V�͂Ȃ����̂Ƃ��� D3D11_USAGE_DEFAULT �Ő����B
	if (!m_vertexBuffer.Create(m_vertices))
	{
		return false;
	}

	// CPU������̍X�V�͂Ȃ����̂Ƃ��� D3D11_USAGE_DEFAULT �Ő����B
	if (!m_indexBuffer.Create(m_indices))
	{
		return false;
	}
	return true;
}