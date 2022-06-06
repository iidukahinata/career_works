/**
* @file    Sprite.cpp
* @brief
*
* @date	   2022/06/06 2022�N�x����
* @author  �ђ˗z��
*/


#include "Sprite.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/Geometry/Plane.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

void Sprite::Init(const SpriteDesc& desc)
{
	m_mesh = Plane::Make<Vertex2D>(desc.width, desc.height);

	// �ǂݍ��ݑ҂����N���Ȃ��悤���񏈗��ōs��
	ThreadPool::Get().AddTask([this, desc]
	{
		// �w�肳�ꂽPath��D�悵�Ēǉ�
		if (!desc.filePath.empty())
		{
			m_mesh.AddTexture(ResourceManager::Get().Load<D3D11Texture>(desc.filePath));
		}

		// �ǂݍ��܂�Ă���f�[�^�����鎞�̂ݏ���
		for (auto texture : desc.textures)
		{
			m_mesh.AddTexture(texture);
		}
	});

	// ���_�V�F�[�_�[����
	m_vertexShader.Create(desc.vsShader);
	m_inputLayout.Create(desc.layout, desc.layoutSize, m_vertexShader.GetBlob());

	//�s�N�Z���V�F�[�_�[����
	m_pixelShader.Create(desc.psShader);

	// �T���v���[����
	m_samplerState.Create();
}

void Sprite::Draw(const DirectX::XMMATRIX& world)
{
	// ���_�V�F�[�_�[�̃p�����[�^�Z�b�g
	m_vertexShader.VSSet();
	
	// �s�N�Z���V�F�[�_�[�̃p�����[�^�Z�b�g
	m_pixelShader.PSSet();
	m_samplerState.PSSet();

	// ���_���C�A�E�g�̃p�����[�^�Z�b�g
	m_inputLayout.IASet();

	// �v���~�e�B�u�^�C�v���Z�b�g
	D3D11GrahicsDevice::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	TransformCBuffer::Get().Bind(world);

	m_mesh.Draw();
}