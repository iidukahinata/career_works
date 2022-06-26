/**
* @file		ModelLoader.cpp
* @brief
*
* @date		2022/05/06 2022年度初版
* @author	飯塚陽太
*/


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <filesystem>
#include "ModelLoader.h"
#include "SubSystem/Resource/ResourceManager.h" 

Model ModelLoader::Load(std::string_view filePath)
{
	m_aiScene = aiImportFile(
		filePath.data(),
		aiProcess_ConvertToLeftHanded |
		aiProcessPreset_TargetRealtime_MaxQuality);

	ProcessNode(m_aiScene->mRootNode);

	return m_model;
}

void ModelLoader::Release() noexcept
{
	aiReleaseImport(m_aiScene);
}

void ModelLoader::ProcessNode(aiNode* node)
{
	// 2022/05/01時点ではアニメーション等は読み込まない
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		LoadMesh(m_aiScene->mMeshes[node->mMeshes[i]]);
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i]);
	}
}

void ModelLoader::LoadMesh(aiMesh* aiMesh)
{
	std::vector<VertexBump3D> vertices;
	std::vector<uint32_t> indices;

	vertices.resize(aiMesh->mNumVertices);
	for (int i = 0; i < aiMesh->mNumVertices; ++i)
	{
		// Meshから頂点座標を取得
		vertices[i].position.x = aiMesh->mVertices[i].x;
		vertices[i].position.y = aiMesh->mVertices[i].y;
		vertices[i].position.z = aiMesh->mVertices[i].z;

		// Meshから法線を取得
		if (aiMesh->HasNormals())
		{
			vertices[i].normal.x = aiMesh->mNormals[i].x;
			vertices[i].normal.y = aiMesh->mNormals[i].y;
			vertices[i].normal.z = aiMesh->mNormals[i].z;
		}

		// MeshからUV座標を取得
		if (aiMesh->HasTextureCoords(0))
		{
			vertices[i].tex.x = aiMesh->mTextureCoords[0][i].x;
			vertices[i].tex.y = aiMesh->mTextureCoords[0][i].y;
		}
	}

	if (aiMesh->mMaterialIndex >= 0)
	{
		LoadMaterial(m_aiScene->mMaterials[aiMesh->mMaterialIndex]);
	}

	Math::Vector3 cp[3][3];
	for (int face_i = 0; face_i < aiMesh->mNumFaces; ++face_i)
	{
		aiFace* face = &aiMesh->mFaces[face_i];
		for (int index_i = 0; index_i < face->mNumIndices; ++index_i)
		{
			int i = face->mIndices[index_i];
			indices.push_back(i);

			cp[index_i][0] = Math::Vector3(vertices[i].position.x, vertices[i].tex.x, vertices[i].tex.y);
			cp[index_i][1] = Math::Vector3(vertices[i].position.y, vertices[i].tex.x, vertices[i].tex.y);
			cp[index_i][2] = Math::Vector3(vertices[i].position.z, vertices[i].tex.x, vertices[i].tex.y);
		}

		// 接ベクトル & 従ベクトル計算
		Math::Vector3 tangent, binormal;
		for (int i = 0; i < 3; ++i)
		{
			auto V1 = cp[1][i] - cp[0][i];
			auto V2 = cp[2][i] - cp[1][i];
			auto ABC = Math::Vector3::Cross(std::move(V1), std::move(V2));

			if (ABC.x == 0.f)
			{
				tangent[i] = 0.f;
				binormal[i] = 0.f;
			}
			else
			{
				tangent[i] = -ABC.y / ABC.x;
				binormal[i] = -ABC.z / ABC.x;
			}
		}

		// Normalize
		tangent.Normalize();
		binormal.Normalize();

		for (int vertex_i = 2; vertex_i >= 0; --vertex_i)
		{
			const int i = face->mIndices[vertex_i];
			vertices[i].tangent = tangent;
			vertices[i].biNormal = binormal;
		}
	}

	m_model.AddMesh(std::move(vertices), std::move(indices));
}

void ModelLoader::LoadMaterial(aiMaterial* aiMaterial)
{
	std::vector<Texture*> textures;

	std::vector<Texture*> diffuseMaps = LoadTextures(aiMaterial);

	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
}

std::vector<Texture*> ModelLoader::LoadTextures(aiMaterial* aiMaterial)
{
	std::vector<Texture*> textures;
	// マテリアルからテクスチャ個数を取得し(基本は1個)ループする
	for (unsigned int i = 0; i < aiMaterial->GetTextureCount(aiTextureType_DIFFUSE); ++i)
	{
		aiString str;
		// マテリアルからｉ番目のテクスチャファイル名を取得する
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);

		// まだ読み込まれていなかった場合
		//if (!ResourceManager::Get().GetResourceByName<Texture>(str.C_Str()))
		//{
		//	std::string_view path(str.C_Str());
		//
		//	std::string filePath(m_textureDirectory);
		//	filePath += path.substr(path.find_last_of("\\/"), path.length() - 1);
		//
		//	textures.push_back(ResourceManager::Get().Load<Texture>(filePath));
		//}
	}

	return textures;
}