/**
* @file    ModelDate.h
* @brief
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
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

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B */
	void SaveToFile(std::string_view filePath);

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B */
	bool LoadFromFile(std::string_view filePath);

private:

	std::vector<Mesh<VertexBump3D>> m_meshes;
};