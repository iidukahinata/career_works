/**
* @file    Human.cpp
* @brief
*
* @date	   2022/06/03 2022�N�x����
* @author  �ђ˗z��
*/


#include "Human.h"

void Human::Awake()
{
	// ���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	ModelDesc modelDesc;
	modelDesc.modelFilePath = "assets/Imqube/Human/Human.x";
	modelDesc.layout = vertexDesc;
	modelDesc.layoutSize = ARRAYSIZE(vertexDesc);
	m_model.Init(modelDesc);
}

void Human::Init()
{
	Math::Vector3 massPos(m_massPos.x, m_massPos.y, m_massPos.z);
	m_transform.SetPosition(Math::Vector3(0.75f * massPos.x, 0.75f * massPos.y - 0.5f, 0.75f * massPos.z));
}

void Human::Update()
{
	constexpr float rad = Math::ToRadian(1.f);
	RotationWorld(Math::Vector3(0.f, rad, 0.f));

	m_transform.SetScale(m_transform.GetScale() + Math::Vector3(0.f, m_animSpeed, 0.f));
	if (m_transform.GetScale().y >= m_maxSizeY && m_animSpeed > 0.f)
	{
		m_animSpeed *= -1.f;
	}
	else if (m_transform.GetScale().y <= m_minSizeY && m_animSpeed < 0.f)
	{
		m_animSpeed *= -1.f;
	}
}

void Human::RotationWorld(const Math::Vector3& angle) noexcept
{
	auto mat = m_transform.GetLocalMatrix();

	// ��]�s��݂̂̏��ɂ��邽��
	mat *= (1.f / m_transform.GetScale().x);

	mat *= Math::Matrix::CreateRotation(angle);

	m_transform.SetRotation(mat.GetEulerAngles());
}

void Human::Draw()
{
	m_model.Draw(m_transform.GetWorldMatrixXM());
}

IMass::MassType Human::GetType()
{
	return MassType::HUMAN;
}