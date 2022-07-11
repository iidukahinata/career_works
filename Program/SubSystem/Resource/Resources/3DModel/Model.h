/**
* @file    Model.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../IResource.h"

class Mesh;
class Material;

class Model : public IResource
{
	SUB_CLASS(Model)
public:

	/** 独自モデルデータとして保存させる。*/
	void SaveToFile(StringView filePath) override;

	/** 独自モデルデータを読み込みする。*/
	bool LoadFromFile(StringView filePath) override;

	void AddMesh(Mesh* mesh) noexcept;
	void AddMaterial(Material* material) noexcept;

	void Render();

private:

	// IResource
	bool Do_Load(StringView filePath) override;

	String ConvertProprietaryFormat(StringView filePath) const noexcept;

private:

	Vector<Mesh*> m_meshes;
	Vector<Material*> m_materials;
};