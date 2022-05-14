/**
* @file		ModelLoader.h
* @brief
*
* @date		2022/05/06 2022îNìxèâî≈
* @author	î—íÀózëæ
*/
#pragma once


#include <assimp/scene.h>
#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Resource/Resources/3DModel/Mesh.h"

class ModelLoader
{
public:

	std::vector<Mesh<VertexBump3D>> Load(std::string_view filePath);

private:

	void Release() noexcept;

	void ProcessNode(aiNode* node);
	void LoadMesh(aiMesh* aiMesh);
	std::vector<Texture*> LoadTextures(aiMaterial* aiMaterial);

	std::string LookForTextureFolder(std::string_view path);

private:

	const aiScene* m_aiScene = nullptr;

	std::vector<Mesh<VertexBump3D>> m_meshes;

	std::string m_textureDirectory;
};