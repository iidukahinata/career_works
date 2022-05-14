/**
* @file    Model.cpp
* @brief
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/


#include "Model.h"
#include <filesystem>
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

Model::Model(const Model& model)
{
	this->operator=(model);
}

Model& Model::operator=(const Model& model)
{
	m_vertexShader = model.m_vertexShader;
	m_inputLayout = model.m_inputLayout;
	m_pixelShader = model.m_pixelShader;
	m_samplerState = model.m_samplerState;

	m_modelData = model.m_modelData;
	m_modelData->AddRefreneceCount();

	return *this;
}

Model::~Model()
{
	// �g�p���Ȃ��Ȃ�������m�点��B
	m_modelData->SubReneceCount();
}

void Model::Init(const ModelDesc& desc)
{
	// �ǂݍ��ݑ҂����N���Ȃ��悤���񏈗��ōs��
	ThreadPool::Get().AddTask([this, desc]
	{
		if (desc.modelFilePath)
		{
			m_modelData = ResourceManager::Get().Load<ModelData>(desc.modelFilePath);
		}

		if (desc.textureFolderPath)
		{
			LoadTextures(desc.textureFolderPath);
		}
	});

	// ���_�V�F�[�_�[����
	m_vertexShader.Create(desc.vsShader);
	m_inputLayout.Create(desc.layout, desc.layoutSize, m_vertexShader.GetBlob());

	// �s�N�Z���V�F�[�_�[����
	m_pixelShader.Create(desc.psShader);

	// �T���v���[����
	m_samplerState.Create(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP);
}

void Model::Draw(const DirectX::XMMATRIX& world)
{
	if (!m_modelData)
		return;

	// ���_�V�F�[�_�[�̃p�����[�^�Z�b�g
	m_vertexShader.VSSet();

	// �s�N�Z���V�F�[�_�[�̃p�����[�^�Z�b�g
	m_pixelShader.PSSet();
	m_samplerState.PSSet();

	// ���_���C�A�E�g�̃p�����[�^�Z�b�g
	m_inputLayout.IASet();

	// �v���~�e�B�u�^�C�v���Z�b�g
	D3D11GrahicsDevice::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_modelData->Draw(world);
}

void Model::LoadTextures(std::string_view textureFolderPath)
{
	if (!m_modelData)
		return;

	// �w��t�H���_���̃f�[�^���擾
	for (const auto& entry : std::filesystem::recursive_directory_iterator(textureFolderPath))
	{
		m_modelData->LoadTexture(entry.path().string().c_str());
	}
}