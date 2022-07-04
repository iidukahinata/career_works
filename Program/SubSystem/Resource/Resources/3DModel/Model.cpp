/**
* @file    Model.cpp
* @brief
*
* @date	   2022/07/01 2022年度初版
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

	// Mesh 書き込み
	fileStream.Write(m_meshes.size());
	for (auto& mesh : m_meshes)
	{
		fileStream.Write(mesh->GetName());
	};

	// Material 書き込み
	fileStream.Write(m_materials.size());
	for (auto& material : m_materials)
	{
		fileStream.Write(material->GetName());
	};
}

bool Model::LoadFromFile(std::string_view filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	// Mesh 読み込み
	size_t numMesh = 0;
	fileStream.Read(&numMesh);

	std::vector<std::string> meshPaths(numMesh);
	for (auto& path : meshPaths)
	{
		fileStream.Read(&path);
	}

	// Material 読み込み
	size_t numMaterial = 0;
	fileStream.Read(&numMaterial);

	std::vector<std::string> materialPaths(numMaterial);
	for (auto& path : materialPaths)
	{
		fileStream.Read(&path);
	}

	fileStream.Close();

	if (const auto resoureManager = GetContext()->GetSubsystem<ResourceManager>())
	{
		for (auto& path : meshPaths)
		{
			AddMesh(resoureManager->Load<Mesh>(path));
		}

		for (auto& path : materialPaths)
		{
			AddMaterial(resoureManager->Load<Material>(path));
		}
	}

	return m_meshes.empty() == false;
}

void Model::AddMesh(Mesh* mesh) noexcept
{
	m_meshes.emplace_back(mesh);
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
		mesh->Render();
	
		context->DrawIndexed(static_cast<UINT>(mesh->GetIndices().size()), 0, 0);
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