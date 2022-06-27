/**
* @file		ModelLoader.h
* @brief
*
* @date		2022/06/26 2022îNìxèâî≈
*/
#pragma once


#include <assimp/scene.h>
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class ModelLoader
{
public:

	bool Load(Model* model, std::string_view filePath);

private:

	void Release() noexcept;

	void ProcessNode(aiNode* node);
	void LoadMesh(aiMesh* aiMesh);
	void LoadMaterial(aiMaterial* aiMaterial);

	std::vector<Texture*> LoadTextures(aiMaterial* aiMaterial);

private:

	const aiScene* m_aiScene = nullptr;

	Model* m_model;
};