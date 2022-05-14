/**
* @file    Mesh.h
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "SubSystem/Renderer/D3D11/D3D11Texture.h"
#include "SubSystem/Renderer/D3D11/D3D11VertexBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11IndexBuffer.h"

/**
* �e���v���[�g�̓��[�U�[�C�ӂ̌^�𒸓_�f�[�^�Ƃ��Ďg�p�B
* �C���f�b�N�X�o�b�t�@�� unsigned short �͑Ή����Ă��Ȃ��B
*/
template<class T>
class Mesh
{
public:

	Mesh() = default;

	/** ���\�[�X�̎Q�Ɛ���ύX����K�v�����邽�߁A�R�s�[�֐����I�o�[���C�h����B*/
	Mesh(const Mesh& mesh);
	Mesh& operator=(const Mesh& mesh);

	Mesh(const std::vector<T>& vertices, const std::vector<Texture*>& textures, const std::vector<UINT>& indices);

	~Mesh();

	void Draw() noexcept;

	void AddTexture(Texture* texture) noexcept;

	/** �A�N�Z�X */
	std::vector<T>& GetVertices() noexcept;
	std::vector<UINT>& GetIndices() noexcept;
	std::vector<Texture*>& GetTextures() noexcept;

private:

	bool SetUp() noexcept;

private:

	std::vector<T> m_vertices;
	std::vector<UINT> m_indices;

	// * �e�N�X�`���̓}�e���A���Ɉڍs����\��B
	std::vector<Texture*> m_textures;

	D3D11VertexBuffer<T> m_vertexBuffer;
	D3D11IndexBuffer m_indexBuffer;
};

template<class T>
inline Mesh<T>::Mesh(const Mesh& mesh)
{
	this->operator=(mesh);
}

template<class T>
Mesh<T>::Mesh(const std::vector<T>& vertices, const std::vector<Texture*>& textures, const std::vector<UINT>& indices) 
	: m_vertices(vertices), m_textures(textures), m_indices(indices)
{
	SetUp();
}

template<class T>
inline Mesh<T>& Mesh<T>::operator=(const Mesh<T>& mesh)
{
	m_vertices = mesh.m_vertices;
	m_indices = mesh.m_indices;
	m_textures = mesh.m_textures;

	m_vertexBuffer = mesh.m_vertexBuffer;
	m_indexBuffer = mesh.m_indexBuffer;

	for (auto& texture : m_textures)
	{
		texture->AddRefreneceCount();
	}

	return *this;
}

template<class T>
Mesh<T>::~Mesh()
{
	// �g�p���Ȃ��Ȃ�������m�点��B
	for (auto& texture : m_textures)
	{
		texture->SubReneceCount();
	}
}

template<class T>
void Mesh<T>::Draw() noexcept
{
	// �e�N�X�`���̃p�����[�^�Z�b�g
	for (int i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i]->Bind(i);
	}

	// ���_�o�b�t�@�̃p�����[�^�Z�b�g
	m_vertexBuffer.IASet();

	// �C���f�b�N�X�o�b�t�@�̃p�����[�^�Z�b�g
	m_indexBuffer.IASet();

	D3D11GrahicsDevice::Get().GetContext()->DrawIndexed(static_cast<UINT>(m_indices.size()), 0, 0);
}

template<class T>
void Mesh<T>::AddTexture(Texture* texture) noexcept
{
	if (texture) 
	{
		m_textures.push_back(texture);
	}
}

template<class T>
std::vector<T>& Mesh<T>::GetVertices() noexcept
{
	return m_vertices;
}

template<class T>
std::vector<UINT>& Mesh<T>::GetIndices() noexcept
{
	return m_indices;
}

template<class T>
inline std::vector<Texture*>& Mesh<T>::GetTextures() noexcept
{
	return m_textures;
}

template<class T>
bool Mesh<T>::SetUp() noexcept
{
	// CPU������̍X�V�͂Ȃ����̂Ƃ��� D3D11_USAGE_DEFAULT �Ő����B
	if (!m_vertexBuffer.Create(m_vertices))
	{
		return false;
	}

	// CPU������̍X�V�͂Ȃ����̂Ƃ��� D3D11_USAGE_DEFAULT �Ő����B
	if (!m_indexBuffer.Create(m_indices))
	{
		return false;
	}
	return true;
}