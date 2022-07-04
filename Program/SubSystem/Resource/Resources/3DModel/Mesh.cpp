/**
* @file    Mesh.cpp
* @brief
*
* @date	   2022/07/01 2022年度初版
*/


#include "Mesh.h"
#include "SubSystem/Core/IO/FileStream.h"
#include "SubSystem/Core/IO/FileSystem.h"

void Mesh::Construct(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices) noexcept
{
	m_vertices = vertices;
	m_indices = indices;
	SetUp();
}

void Mesh::SaveToFile(std::string_view filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream;
	fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode);
	if (!fileStream.IsOpen())
		return;

	fileStream.Write(m_vertices);
	fileStream.Write(m_indices);
}

bool Mesh::LoadFromFile(std::string_view filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream;
	fileStream.Load(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	fileStream.Read(&m_vertices);
	fileStream.Read(&m_indices);

	return SetUp();
}

void Mesh::SetVertices(const std::vector<VertexBump3D>& vertices) noexcept
{
	m_vertices = vertices;
}

const std::vector<VertexBump3D>& Mesh::GetVertices() noexcept
{
	return m_vertices;
}

void Mesh::SetIndices(const std::vector<uint32_t>& indices) noexcept
{
	m_indices = indices;
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

std::string Mesh::ConvertProprietaryFormat(std::string_view filePath) const noexcept
{
	std::string path = "assets/Resource/Mesh/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	std::string_view sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".mesh";

	return path;
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