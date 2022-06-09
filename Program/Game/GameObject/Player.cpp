/**
* @file    Player.cpp
* @brief
*
* @date	   2022/06/08 2022�N�x����
* @author  �ђ˗z��
*/


#include "Player.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"
#include "Stage.h"
#include "Human.h"
#include "CameraMove.h"

void Player::Awake()
{
	// ���_���C�A�E�g�쐬
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
}

void Player::Init()
{
	m_cameraMove = dynamic_cast<CameraMove*>(m_scene->GetGameObject("cameraMove"));
	m_stage = dynamic_cast<Stage*>(m_scene->GetGameObject("stage"));

	Math::Vector3 massPos(m_massPos.x, m_massPos.y, m_massPos.z);
	m_transform.SetPosition(Math::Vector3(0.75f * massPos.x, 0.75f * massPos.y, 0.75f * massPos.z));
	m_transform.SetScale(Math::Vector3(0.05f));
}

void Player::Update()
{
	if (m_hitStop.IsHitStop())
		return;

	// enemy �̈ړ����l�����邽�� ���́A��]�̊O�ōs���B
	ChackTheNextMassFromStage();

	InputAction();

	Rolling();
}

void Player::Draw()
{
	m_model.Draw(m_transform.GetWorldMatrixXM());
}

const char* Player::GetName()
{
	return "player";
}

IMass::MassType Player::GetType()
{
	return MassType::PLAYER;
}

void Player::InputAction() noexcept
{
	if (IsInput())
	{
		return;
	}

	// �J�����̌�������ړ����������߂邽�߁A�e�������ɈႤ�������s��
	if (Input::Get().GetKeyStatePress(Button::Left))
	{
		m_angle = m_cameraMove->GetDirection();
		m_angle = Math::Vector2(m_angle.y, m_angle.x);
	}
	if (Input::Get().GetKeyStatePress(Button::Right))
	{
		m_angle = -m_cameraMove->GetDirection();
		m_angle = Math::Vector2(m_angle.y, m_angle.x);
	}
	if (Input::Get().GetKeyStatePress(Button::Up))
	{
		m_angle = m_cameraMove->GetDirection();
		if (m_cameraMove->GetDirection().x != 0) m_angle.x *= -1.f;
	}
	if (Input::Get().GetKeyStatePress(Button::Down))
	{
		m_angle = -m_cameraMove->GetDirection();
		if (m_cameraMove->GetDirection().x != 0) m_angle.x *= -1.f;
	}

	if (IsInput())
	{
		// �����͍l�����Ă��Ȃ�
		m_nextMassPos.x += -m_angle.x;
		m_nextMassPos.z +=  m_angle.y;
		m_nextMassPos.y = m_massPos.y;

		m_stage->RemoveMass(this);
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
	constexpr float halfMassSize = 0.8333f;
	const float commonValue = halfMassSize * static_cast<float>(m_rotateSpeed);

	auto pos = m_transform.GetPosition();

	pos.x += m_massSize.x * -m_angle.x * commonValue;
	pos.z += m_massSize.z * m_angle.y * commonValue;

	// �����ɂ��ꂪ�����邽�� 0 ���O��
	// player �ړ��𓙉����x�^���ɕύX����ꍇ�́A���L�R�[�h���C������K�v������B
	if (m_angleCount > 0) pos.y += m_massSize.y * (static_cast<float>(45 - m_angleCount) / 45.f) * commonValue;

	m_transform.SetPosition(pos);
}

void Player::Rotation90Degree() noexcept
{
	m_angleCount += m_rotateSpeed;

	constexpr float rad = Math::ToRadian(1.f);
	RotationWorld(Math::Vector3(m_angle.y * rad, 0.f, m_angle.x * rad) * static_cast<float>(m_rotateSpeed));

	if (m_angleCount >= 90)
	{
		FinishRolling();
	}
}

void Player::ChackTheNextMassFromStage() noexcept
{
	auto nextMassType = m_stage->GetMassType(m_nextMassPos);
	switch (nextMassType)
	{
	case FLOOR: break;
	case MESSAGE: break;
	case PUTENEMY: break;
	case NONE: m_isGameOver = true; break;
	default: break;
	}
}

void Player::ChackTheNextMassFromMap() noexcept
{
	if (auto nextMass = m_stage->GetMassData(m_nextMassPos))
	{
		switch (nextMass->GetType())
		{
		case MassType::PLAYER: break;
		case MassType::ENEMY: HitEnemy(nextMass); break;
		case MassType::HUMAN: HitHuman(nextMass); break;
		case MassType::MESSEGE: break;
		default: break;
		}
	}
}

void Player::HitHuman(IMass* hitMass) noexcept
{
	// ��]��Ɏ擾��������邽��
	if (IsInput())
	{
		return;
	}

	if (isGetHuman[GetNowBottomSurface()])
	{
		m_isGameOver = true;
	}
	else
	{
		isGetHuman[GetNowBottomSurface()] = true;

		m_stage->RemoveMass(hitMass);
		m_scene->RemoveGameObject(hitMass);
	}
}

void Player::HitEnemy(IMass* hitMass) noexcept
{
	if (IsInput())
	{
		if (isGetHuman[GetNowBottomSurface()])
		{

		}
		else
		{
			m_isGameOver = true;
		}
	}
	else
	{
		m_isGameOver = true;
	}
}

void Player::RotationWorld(const Math::Vector3& angle) noexcept
{
	auto mat = m_transform.GetLocalMatrix();

	// ��]�s��݂̂̏��ɂ��邽��
	mat *= (1.f / m_transform.GetScale().x);

	mat *= Math::Matrix::CreateRotation(angle);

	m_transform.SetRotation(mat.GetEulerAngles());
}

void Player::FinishRolling() noexcept
{
	m_angle = Math::Vector2();
	m_angleCount = 0;
	m_massPos = m_nextMassPos;

	m_hitStop.Start(3);

	ChackTheNextMassFromStage();
	ChackTheNextMassFromMap();

	m_stage->SetMass(m_massPos, this);
}

BOX_FACE_INFO Player::GetNowBottomSurface() noexcept
{
	auto chack = [](const auto& right, const auto& up, const auto& forward)
	{
		if (abs(right.y + 1.f) <= 0.001f)
		{
			return BOX_FACE_INFO::POSITIVE_X;
		}
		if (abs(up.y + 1.f) <= 0.001f)
		{
			return BOX_FACE_INFO::POSITIVE_Y;
		}
		if (abs(forward.y + 1.f) <= 0.001f)
		{
			return BOX_FACE_INFO::POSITIVE_Z;
		}
		return BOX_FACE_INFO::Max;
	};

	auto right = m_transform.GetRight();
	auto up = m_transform.GetUp();
	auto forward = m_transform.GetForward();

	int bottomSurface = chack(right, up, forward);
	if (bottomSurface < BOX_FACE_INFO::Max)
	{
		return static_cast<BOX_FACE_INFO>(bottomSurface);
	}

	bottomSurface = chack(-right, -up, -forward);
	if (bottomSurface < BOX_FACE_INFO::Max)
	{
		return static_cast<BOX_FACE_INFO>(bottomSurface + BOX_FACE_INFO::NEGATIVE_X);
	}
	return BOX_FACE_INFO::Max;
}

int Player::InputNum() const noexcept
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_angle[i] != 0) return i;
	}
	return -1;
}

bool Player::IsInput() const noexcept
{
	return m_angle.x != 0 || m_angle.y != 0;
}

bool Player::isGameOver() const noexcept
{
	return m_isGameOver;
}