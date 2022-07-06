/**
* @file		ModelLoader.h
* @brief
*
* @date		2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include <assimp/scene.h>
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class ModelLoader
{
public:

	ModelLoader();
	bool Load(Model* model, String_View filePath);

private:

	void Release() noexcept;

	void ProcessNode(aiNode* node);
	void LoadMesh(aiMesh* aiMesh);
	void LoadMaterial(aiMaterial* aiMaterial);

	Vector<Texture*> LoadTextures(aiMaterial* aiMaterial);

private:

	const aiScene* m_aiScene = nullptr;

	Model* m_model;

	class ResourceManager* m_resourceManager;
};