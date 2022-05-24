

#include "Player.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"

void Player::Init()
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	ModelDesc modelDesc;
	modelDesc.modelFilePath = "assets/Dice/Box.x";
	modelDesc.layout = vertexDesc;
	modelDesc.layoutSize = ARRAYSIZE(vertexDesc);
	m_model.Init(modelDesc);

	m_transform.SetScale(Math::Vector3(0.05f));
}

void Player::Update()
{
	InputAction();

	Rolling();
}

void Player::Draw()
{
	m_model.Draw(m_transform.GetWorldMatrixXM());
}

void Player::InputAction() noexcept
{
	if (IsInput())
	{
		return;
	}

	if (Input::Get().GetKeyStateTrigger(Button::Left))
	{
		m_angles[0] = 1;
	}
	if (Input::Get().GetKeyStateTrigger(Button::Right))
	{
		m_angles[0] = -1;
	}
	if (Input::Get().GetKeyStateTrigger(Button::Up))
	{
		m_angles[1] = 1;
	}
	if (Input::Get().GetKeyStateTrigger(Button::Down))
	{
		m_angles[1] = -1;
	}
}

void Player::Rolling() noexcept
{
	if (!IsInput())
	{
		return;
	}

	Move1Mass();

	Rotation90Degree();
}

void Player::Move1Mass() noexcept
{
	auto pos = m_transform.GetPosition();

	pos.x += m_angles[0];
	pos.y += 0.f;
	pos.z += m_angles[1];
}

void Player::Rotation90Degree() noexcept
{
	++m_angleCount;

	constexpr float rad = Math::ToRadian(1.f);
	RotationWorld(Math::Vector3(m_angles[1] * rad, 0.f, m_angles[0] * rad));

	if (m_angleCount == 90)
	{
		FinishRotate();
	}
}

void Player::RotationWorld(const Math::Vector3& angle) noexcept
{
	auto mat = m_transform.GetLocalMatrix();

	// 回転行列のみの情報にするため
	mat *= (1.f / m_transform.GetScale().x);

	mat *= Math::Matrix::CreateRotation(angle);

	m_transform.SetRotation(mat.GetEulerAngles());
}

void Player::FinishRotate() noexcept
{
	for (int i = 0; i < AngleSize; ++i)
	{
		m_angles[i] = 0;
	}

	m_angleCount = 0;
}

int Player::InputNum() const noexcept
{
	for (int i = 0; i < AngleSize; ++i)
	{
		if (m_angles[i] != 0) return i;
	}
	return -1;
}

bool Player::IsInput() const noexcept
{
	return m_angles[0] != 0 || m_angles[1] != 0;
}