/**
* @file	   SkyBox.cpp
* @brief
*
* @date	   2022/04/29 2022�N�x����
* @author  �ђ˗z��
*/


#include "SkyBox.h"
#include "Application/Application.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/Geometry/Cube.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

bool SkyBox::Init(const std::string& filePath)
{
	// �L���[�u�}�b�v����
	m_meshes.emplace_back(Cube::Make<Vertex3D>());

	// �ǂݍ��ݑ҂����N���Ȃ��悤���񏈗��ōs��
	ThreadPool::Get().AddTask([this, filePath]
	{
		m_meshes[0].AddTexture(ResourceManager::Get().Load<D3D11Texture>(filePath.c_str()));
	});

	SetUp();

	m_transform.SetScale(Math::Vector3(1000));

	return true;
}

void SkyBox::Draw(const Math::Vector3& cameraPos)
{
	auto context = D3D11GrahicsDevice::Get().GetContext();

	// ���_�V�F�[�_�[�̃p�����[�^�Z�b�g
	m_vertexShader.VSSet();

	// �s�N�Z���V�F�[�_�[�̃p�����[�^�Z�b�g
	m_pixelShader.PSSet();
	m_samplerState.PSSet(0);

	// ���_���C�A�E�g�ƃv���~�e�B�u�^�C�v���Z�b�g
	m_inputLayout.IASet();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_transform.SetPosition(cameraPos);
	TransformCBuffer::Get().Bind(m_transform.GetLocalMatrixXM());

	for (auto& mesh : m_meshes)
	{
		mesh.Draw();
	}
}

bool SkyBox::SetUp()
{
	auto device = D3D11GrahicsDevice::Get().GetDevice();

	// ���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0							, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// ���_�V�F�[�_�[����
	m_vertexShader.Create("assets/Shader/BoxVS.cso");
	m_inputLayout.Create(layout, ARRAYSIZE(layout), m_vertexShader.GetBlob());

	//�s�N�Z���V�F�[�_�[����
	m_pixelShader.Create("assets/Shader/BoxPS.cso");

	m_samplerState.Create(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP);

	return true;
}