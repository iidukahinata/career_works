/**
* @file    ModelDate.cpp
* @brief
*
* @date	   2022/05/06 2022年度初版
* @author  飯塚陽太
* @note
*  独自modelデータ
*	メッシュ数		 8bit
*	頂点数			 8bit
*	頂点情報		     VertexBump3D * 頂点数 bit
*	インデックス数	 8bit
*	インデックス情報 UINT * 頂点数 bit
*/


#include "ModelData.h"
#include "SubSystem/Core/IO/FileStream.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Resource/ResourceLoader/ModelLoader/ModelLoader.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Core/Common/Tools.h"

void ModelData::Draw(const DirectX::XMMATRIX& world)
{
	TransformCBuffer::Get().Bind(world);

	for (auto& mesh : m_meshes) {
		mesh.Draw();
	}
}

bool ModelData::LoadTexture(std::string_view filePath)
{
	//if (auto texture = ResourceManager::Get().Load<D3D11Texture>(filePath)) {
	//	m_meshes[0].AddTexture(texture);
	//	return true;
	//}
	return false;
}

bool ModelData::Do_Load(std::string_view filePath)
{
	// 読み込む時間短縮のため独自データがあるか調べる
	if (LoadFromFile(filePath))
		return true;

	ModelLoader modelLoader;
	m_meshes = modelLoader.Load(filePath);

	// 次回から高速に読み込むために独自データを作成
	SaveToFile(filePath);

	return true;
}

void ModelData::SaveToFile(std::string_view filePath)
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
	
		fileStream.Write(mesh.GetTextures().size());
		for (auto& texture : mesh.GetTextures()) 
		{
			fileStream.Write(texture->GetName());
		}
	}
}

bool ModelData::LoadFromFile(std::string_view filePath)
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
		std::vector<Texture*> textures;
		std::vector<UINT> indices;

		fileStream.Read(&vertices);
		fileStream.Read(&indices);

		size_t textureSize;
		fileStream.Read(&textureSize);
		
		textures.resize(textureSize);
		for (int i = 0; i < textureSize; ++i)
		{
			std::string texturePath;
			fileStream.Read(&texturePath);
		
			//textures[i] = ResourceManager::Get().Load<D3D11Texture>(texturePath);
		}

		m_meshes.emplace_back(std::move(vertices), std::move(textures), std::move(indices));
	}

	if (m_meshes.empty()) 
	{
		return false;
	}
	return true;
}