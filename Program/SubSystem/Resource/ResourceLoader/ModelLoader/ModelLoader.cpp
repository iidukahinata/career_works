/**
* @file		ModelLoader.cpp
* @brief
*
* @date		2022/07/06 2022年度初版
*/


#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include "ModelLoader.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Core/IO/FileSystem.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Resource/Resources/3DModel/Mesh.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"
#include "SubSystem/Resource/Resources/3DModel/Texture.h"
#include "SubSystem/Resource/Resources/3DModel/Material.h"

extern Context* g_context;

ModelLoader::ModelLoader()
{
	m_resourceManager = g_context->GetSubsystem<ResourceManager>();
}

bool ModelLoader::Load(Model* model, String_View filePath)
{
	m_model = model;

	m_aiScene = aiImportFile(filePath.data(), aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);
	if (!m_aiScene)
	{
		return false;
	}

	ProcessNode(m_aiScene->mRootNode);
	Release();

	return true;
}

void ModelLoader::Release() noexcept
{
	if (m_aiScene)
	{
		aiReleaseImport(m_aiScene);
		m_aiScene = nullptr;
	}
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
	Vector<VertexBump3D> vertices;
	Vector<uint32_t> indices;

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

	Mesh* mesh = m_resourceManager->Load<Mesh>(aiMesh->mName.C_Str());
	mesh->Construct(std::move(vertices), std::move(indices));
	m_model->AddMesh(mesh);

	if (aiMesh->mMaterialIndex >= 0)
	{
		LoadMaterial(m_aiScene->mMaterials[aiMesh->mMaterialIndex]);
	}
}

void ModelLoader::LoadMaterial(aiMaterial* aiMaterial)
{
	Material* material = m_resourceManager->Load<Material>(aiMaterial->GetName().C_Str());

	for (auto textures = LoadTextures(aiMaterial); auto texture : textures)
	{
		material->AddTexture(texture);
	}
	m_model->AddMaterial(material);
}

Vector<Texture*> ModelLoader::LoadTextures(aiMaterial* aiMaterial)
{
	Vector<Texture*> textures;
	// マテリアルからテクスチャ個数を取得し(基本は1個)ループする
	for (unsigned int i = 0; i < aiMaterial->GetTextureCount(aiTextureType_DIFFUSE); ++i)
	{
		aiString str;
		// マテリアルからｉ番目のテクスチャファイル名を取得する
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);

		String_View path(str.C_Str());
		path = path.substr(path.find_last_of("\\/"), path.length() - 1);
		auto filePath = FileSystem::Canonical(path);

		textures.push_back(m_resourceManager->Load<Texture>(filePath));
	}

	return textures;
}