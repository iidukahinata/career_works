#include "Model.h"
#include "SubSystem/Core/IO/FileStream.h"

void Model::SaveToFile(std::string_view filePath)
{
	// ファイル拡張子を独自ファイル用に変更
	std::string path(filePath.substr(0, filePath.find(".")));
	path += ".bin";

	FileStream fileStream;
	fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode);
	if (!fileStream.IsOpen())
		return;

	fileStream.Write(m_meshes.size());

	for (auto& mesh : m_meshes)
	{
		fileStream.Write(mesh.GetVertices());
		fileStream.Write(mesh.GetIndices());
	};
}

bool Model::LoadFromFile(std::string_view filePath)
{
	// ファイル拡張子を独自ファイル用に変更
	std::string path(filePath.substr(0, filePath.find(".")));
	path += ".bin";

	FileStream fileStream(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	size_t numMesh;
	fileStream.Read(&numMesh);

	for (int i = 0; i < numMesh; ++i)
	{
		std::vector<VertexBump3D> vertices;
		std::vector<uint32_t> indices;

		fileStream.Read(&vertices);
		fileStream.Read(&indices);

		m_meshes.emplace_back(std::move(vertices), std::move(indices));
	}

	return !m_meshes.empty();
}

void Model::AddMesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices)
{
	m_meshes.push_back(Mesh(vertices, indices));
}

void Model::AddMesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices)
{
	m_meshes.push_back(Mesh(vertices, indices));
}

bool Model::Do_Load(std::string_view filePath)
{
    return false;
}