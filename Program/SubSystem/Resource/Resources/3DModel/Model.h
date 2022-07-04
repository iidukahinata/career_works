/**
* @file    Model.h
* @brief
*
* @date	   2022/07/01 2022年度初版
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
	void SaveToFile(std::string_view filePath) override;

	/** 独自モデルデータを読み込みする。*/
	bool LoadFromFile(std::string_view filePath) override;

	void AddMesh(Mesh* mesh) noexcept;
	void AddMaterial(Material* material) noexcept;

	void Render();

private:

	// IResource
	bool Do_Load(std::string_view filePath) override;

	std::string ConvertProprietaryFormat(std::string_view filePath) const noexcept;

private:

	Mesh m_mesh;
	std::vector<Mesh*> m_meshes;
	std::vector<Material*> m_materials;
};