/**
* @file		ModelLoader.h
* @brief
*
* @date		2022/07/06 2022îNìxèâî≈
*/
#pragma once


struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;

class Model;
class Texture;
class ResourceManager;

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

	ResourceManager* m_resourceManager;
};