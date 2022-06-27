/**
* @file    Model.cpp
* @brief
*
* @date	   2022/06/27 2022年度初版
*/


#include "Model.h"
#include "SubSystem/Core/IO/FileStream.h"
#include "SubSystem/Core/IO/FileSystem.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Resource/ResourceLoader/ModelLoader/ModelLoader.h"

void Model::SaveToFile(std::string_view filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

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

	fileStream.Write(m_materials.size());
	for (auto& material : m_materials)
	{
		fileStream.Write(material->GetName());
	};

	for (auto& material : m_materials)
	{
		material->SaveToFile(material->GetName());
	};
}

bool Model::LoadFromFile(std::string_view filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

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

		AddMesh(std::move(vertices), std::move(indices));
	}

	size_t numMaterial;
	fileStream.Read(&numMaterial);

	std::vector<std::string> names(numMaterial);
	for (int i = 0; i < numMaterial; ++i)
	{
		fileStream.Read(&names[i]);
	}

	auto resoureManager = GetContext()->GetSubsystem<ResourceManager>();
	for (int i = 0; i < numMaterial; ++i)
	{
		AddMaterial(resoureManager->Load<Material>(names[i]));
	}

	return m_meshes.empty() == false;
}

void Model::AddMesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices)
{
	m_meshes.push_back(Mesh(vertices, indices));
}

void Model::AddMesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices)
{
	m_meshes.push_back(Mesh(vertices, indices));
}

void Model::AddMaterial(Material* material) noexcept
{
	m_materials.emplace_back(material);
}

void Model::Render()
{
	auto context = D3D11GrahicsDevice::Get().GetContext();

	// 現在想定は最初の一つのみ
	m_materials[0]->ShaderSet();

	for (auto& mesh : m_meshes)
	{
		mesh.Render();

		context->DrawIndexed(static_cast<UINT>(mesh.GetIndices().size()), 0, 0);
	}
}

bool Model::Do_Load(std::string_view filePath)
{
	ModelLoader modelLoader;
	return modelLoader.Load(this, filePath);
}

std::string Model::ConvertProprietaryFormat(std::string_view filePath) const noexcept
{
	std::string path = "assets/Resource/Model/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	std::string_view sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".model";

	return path;
}