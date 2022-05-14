/**
* @file    ModelDate.h
* @brief
*
* @date	   2022/05/06 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "Mesh.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"

struct ModelData : public IResource
{
public:

	void Draw(const DirectX::XMMATRIX& world);

	bool LoadTexture(std::string_view filePath);

private:

	// IResource
	bool Do_Load(std::string_view filePath) override;

	/** 独自モデルデータとして保存させる。 */
	void SaveToFile(std::string_view filePath);

	/** 独自モデルデータを読み込みする。 */
	bool LoadFromFile(std::string_view filePath);

private:

	std::vector<Mesh<VertexBump3D>> m_meshes;
};