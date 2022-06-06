/**
* @file    Quad.h
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "../3DModel/Mesh.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

/** Quad �̏��������ݒ�̍��ڍ\���� */
struct QuadDesc
{
	// * �l���ݒ肳��Ă��鎞�͉������D�悳��܂��B
	std::string filePath;

	// * filePath �̎��ɓǂݍ��܂�܂��B
	std::vector<Texture*> textures;

	// * null �ȊO�̒l�ł���K�v������܂��B
	D3D11_INPUT_ELEMENT_DESC* layout = nullptr;

	// * layout �z��̗v�f�����w�肵�Ă��������B
	UINT layoutSize = 0;

	// * �g�p����V�F�[�_�[�p�X���w�肵�Ă��������B
	const char* vsShader = "assets/Shader/LambertVS.cso";
	const char* psShader = "assets/Shader/LambertPS.cso";
};

/** �\�̂ݕ`�悳���e�N�X�`���ł��B */
class Quad
{
public:
	
	void Init(const QuadDesc& desc);
	void Draw(const DirectX::XMMATRIX& world);

private:
	
	Mesh<Vertex3D> m_mesh;

	// shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;

	D3D11SamplerState m_samplerState;
};