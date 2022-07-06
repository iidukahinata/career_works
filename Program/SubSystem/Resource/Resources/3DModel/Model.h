/**
* @file    Model.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "Mesh.h"
#include "Material.h"
#include "../IResource.h"

class Model : public IResource
{
	SUB_CLASS(Model)
public:

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B*/
	void SaveToFile(String_View filePath) override;

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B*/
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