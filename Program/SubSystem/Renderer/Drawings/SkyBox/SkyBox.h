/**
* @file	   SkyBox.h
* @brief
*
* @date	   2022/04/29 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"
#include "SubSystem/Resource/Resources/3DModel/Mesh.h"
#include "SubSystem/Scene/Transform.h"

class SkyBox
{
public:

	bool Init(const std::string& filePath);
	void Draw(const Math::Vector3& cameraPos);

private:

	bool SetUp();

private:

	Transform m_transform;

	// * cube map Mesh
	std::vector<Mesh<Vertex3D>> m_meshes;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;
	D3D11SamplerState m_samplerState;
};