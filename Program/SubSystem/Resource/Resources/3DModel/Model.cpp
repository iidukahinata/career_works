/**
* @file    Model.cpp
* @brief
*
* @date	   2022/07/27 2022年度初版
*/


#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Resource/ResourceLoader/ModelLoader/ModelLoader.h"

void Model::SaveToFile(StringView filePath)
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

bool Model::LoadFromFile(StringView filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	// Mesh 読み込み
	size_t numMesh = 0;
	fileStream.Read(&numMesh);

	Vector<String> meshPaths(numMesh);
	for (auto& path : meshPaths)
	{
		fileStream.Read(&path);
	}

	// Material 読み込み
	size_t numMaterial = 0;
	fileStream.Read(&numMaterial);

	Vector<String> materialPaths(numMaterial);
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

void Model::Render() const noexcept
{
	auto commadList = D3D12GraphicsDevice::Get().GetCommandList();

	// 現在想定は最初の一つのみ
	m_materials[0]->ShaderSet();

	for (auto& mesh : m_meshes)
	{
		mesh->Render();
	
		commadList->DrawIndexedInstanced(static_cast<UINT>(mesh->GetIndices().size()), 1, 0, 0, 0);
	}
}

bool Model::Do_Load(StringView filePath)
{
	ModelLoader modelLoader;
	return modelLoader.Load(this, filePath);
}

String Model::ConvertProprietaryFormat(StringView filePath) const noexcept
{
	String path = "assets/Resource/Model/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	StringView sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".model";

	return path;
}