/**
* @file    Model.h
* @brief
*
* @date	   2022/07/01 2022�N�x����
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
	void SaveToFile(std::string_view filePath) override;

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B*/
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