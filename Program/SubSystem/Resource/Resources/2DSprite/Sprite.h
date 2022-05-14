/**
* @file    Sprite.h
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

/** Sprite �̏��������ݒ�̍��ڍ\���� */
struct SpriteDesc
{
	// * �l���ݒ肳��Ă��鎞�͉������D�悳��܂��B
	const char* filePath = nullptr;

	// * filePath �̎��ɓǂݍ��܂�܂��B
	std::vector<Texture*> textures;

	// * null �ȊO�̒l�ł���K�v������܂��B
	D3D11_INPUT_ELEMENT_DESC* layout = nullptr;

	// * layout �z��̗v�f�����w�肵�Ă��������B
	UINT layoutSize = 0;

	// * �g�p����V�F�[�_�[�p�X���w�肵�Ă��������B
	const char* vsShader = "assets/Shader/TextureVS.cso";
	const char* psShader = "assets/Shader/TexturePS.cso";

	// * �e�N�X�`���T�C�Y���w�肵�Ă��������B
	float width = 1.f;
	float height = 1.f;
};

/** �\�������݂��Ȃ��e�N�X�`���ł��B */
class Sprite
{
public:

	Math::Vector4 m_color;

public:

	Sprite();

	void Init(const SpriteDesc& desc);
	void Draw(const DirectX::XMMATRIX& world);

private:

	Mesh<Vertex2D> m_mesh;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;
	D3D11SamplerState m_samplerState;
};