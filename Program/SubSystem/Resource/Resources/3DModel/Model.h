/**
* @file    Model.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "Mesh.h"
#include "Material.h"
#include "../IResource.h"

class Model : public IResource
{
	SUB_CLASS(Model)
public:

	/** 独自モデルデータとして保存させる。*/
	void SaveToFile(String_View filePath) override;

	/** 独自モデルデータを読み込みする。*/
	bool LoadFromFile(String_View filePath) override;

	void AddMesh(Mesh* mesh) noexcept;
	void AddMaterial(Material* material) noexcept;

	void Render();

private:

	// IResource
	bool Do_Load(String_View filePath) override;

	String ConvertProprietaryFormat(String_View filePath) const noexcept;

private:

	Mesh m_mesh;
	Vector<Mesh*> m_meshes;
	Vector<Material*> m_materials;
};