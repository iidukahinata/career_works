/**
* @file		ModelLoader.h
* @brief
*
* @date		2022/05/06 2022îNìxèâî≈
* @author	î—íÀózëæ
*/
#pragma once


#include <assimp/scene.h>
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class ModelLoader
{
public:

	Model Load(std::string_view filePath);

private:

	void Release() noexcept;

	void ProcessNode(aiNode* node);
	void LoadMesh(aiMesh* aiMesh);
	void LoadMaterial(aiMaterial* aiMaterial);

	std::vector<Texture*> LoadTextures(aiMaterial* aiMaterial);

private:

	const aiScene* m_aiScene = nullptr;

	Model m_model;

	std::string m_textureDirectory;
};