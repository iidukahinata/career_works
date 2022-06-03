/**
* @file    Model.h
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "ModelData.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

/** Model �̏��������ݒ�̍��ڍ\���� */
struct ModelDesc
{
	// * �ǂݍ��ރ��f���p�X���w�肵�Ă��������B
	std::string modelFilePath;

	// * �e�N�X�`���������Ă���t�H���_�p�X���w�肵�Ă��������B
	std::string textureFolderPath;

	// * null �ȊO�̒l�ł���K�v������܂��B
	D3D11_INPUT_ELEMENT_DESC* layout = nullptr;

	// * layout �z��̗v�f�����w�肵�Ă��������B
	UINT layoutSize = 0;

	// * �g�p����V�F�[�_�[�p�X���w�肵�Ă��������B
	const char* vsShader = "assets/Shader/LambertVS.cso";
	const char* psShader = "assets/Shader/LambertPS.cso";
};

/** ����e�N�X�`���f�[�^���}�e���A���ɕ���������ɕύX�\��B */
class Model
{
public:

	Model() = default;

	/** ���\�[�X�̎Q�Ɛ���ύX����K�v�����邽�߁A�R�s�[�֐����I�o�[���C�h����B*/
	Model(const Model& model);
	Model& operator=(const Model& model);

	~Model();

	void Init(const ModelDesc& desc);
	void Draw(const DirectX::XMMATRIX& world);

private:

	/** �w��t�H���_���̑S�Ẵe�N�X�`����ǂݍ��� */
	void LoadTextures(std::string_view textureFolderPath);

private:

	ModelData* m_modelData;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;

	D3D11SamplerState m_samplerState;
};