/**
* @file		ModelLoader.cpp
* @brief
*
* @date		2022/06/27 2022�N�x����
*/


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include "ModelLoader.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Core/IO/FileSystem.h"
#include "SubSystem/Resource/ResourceManager.h"

bool ModelLoader::Load(Model* model, std::string_view filePath)
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
	// 2022/05/01���_�ł̓A�j���[�V�������͓ǂݍ��܂Ȃ�
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
		// Mesh���璸�_���W���擾
		vertices[i].position.x = aiMesh->mVertices[i].x;
		vertices[i].position.y = aiMesh->mVertices[i].y;
		vertices[i].position.z = aiMesh->mVertices[i].z;

		// Mesh����@�����擾
		if (aiMesh->HasNormals())
		{
			vertices[i].normal.x = aiMesh->mNormals[i].x;
			vertices[i].normal.y = aiMesh->mNormals[i].y;
			vertices[i].normal.z = aiMesh->mNormals[i].z;
		}

		// Mesh����UV���W���擾
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

		// �ڃx�N�g�� & �]�x�N�g���v�Z
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

	if (aiMesh->mMaterialIndex >= 0)
	{
		LoadMaterial(m_aiScene->mMaterials[aiMesh->mMaterialIndex]);
	}

	m_model->AddMesh(std::move(vertices), std::move(indices));
}

void ModelLoader::LoadMaterial(aiMaterial* aiMaterial)
{
	auto resourceManager = Context::Get().GetSubsystem<ResourceManager>();
	Material* material = resourceManager->Load<Material>(aiMaterial->GetName().C_Str());

	for (auto textures = LoadTextures(aiMaterial); auto texture : textures)
	{
		material->AddTexture(texture);
	}
	m_model->AddMaterial(material);
}

std::vector<Texture*> ModelLoader::LoadTextures(aiMaterial* aiMaterial)
{
	auto resourceManager = Context::Get().GetSubsystem<ResourceManager>();

	std::vector<Texture*> textures;
	// �}�e���A������e�N�X�`�������擾��(��{��1��)���[�v����
	for (unsigned int i = 0; i < aiMaterial->GetTextureCount(aiTextureType_DIFFUSE); ++i)
	{
		aiString str;
		// �}�e���A�����炉�Ԗڂ̃e�N�X�`���t�@�C�������擾����
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);

		std::string_view path(str.C_Str());
		path = path.substr(path.find_last_of("\\/"), path.length() - 1);
		auto filePath = FileSystem::Canonical(path);

		textures.push_back(resourceManager->Load<Texture>(filePath));
	}

	return textures;
}