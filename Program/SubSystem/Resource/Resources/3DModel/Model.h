/**
* @file    Model.h
* @brief
*
* @date	   2022/06/27 2022�N�x����
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

	void AddMesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices);
	void AddMesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices);

	void AddMaterial(Material* material) noexcept;

	void Render();

private:

	// IResource
	bool Do_Load(std::string_view filePath) override;

	std::string ConvertProprietaryFormat(std::string_view filePath) const noexcept;

private:

	std::vector<Mesh> m_meshes;
	std::vector<Material*> m_materials;
};