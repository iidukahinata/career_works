#pragma once


#include "Mesh.h"
#include "Material.h"
#include "../IResource.h"

class Model : public IResource
{
public:

	/** 独自モデルデータとして保存させる。 */
	void SaveToFile(std::string_view filePath) override;

	/** 独自モデルデータを読み込みする。 */
	bool LoadFromFile(std::string_view filePath) override;

	void AddMesh(std::vector<VertexBump3D>&& vertices, std::vector<uint32_t>&& indices);
	void AddMesh(const std::vector<VertexBump3D>& vertices, const std::vector<uint32_t>& indices);

private:

	// IResource
	bool Do_Load(std::string_view filePath) override;

private:

	std::vector<Mesh> m_meshes;
	std::vector<Material> m_materials;
};