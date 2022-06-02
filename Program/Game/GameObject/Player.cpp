/**
* @file    Player.cpp
* @brief
*
* @date	   2022/06/01 2022年度初版
* @author  飯塚陽太
*/


#include "Player.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"
#include "Stage.h"
#include "CameraMove.h"
#include "Message.h"

void Player::Awake()
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
}

void Player::Init()
{
	m_cameraMove = dynamic_cast<CameraMove*>(m_scene->GetGameObject("cameraMove"));
	m_stage = dynamic_cast<Stage*>(m_scene->GetGameObject("stage"));

	m_transform.SetScale(Math::Vector3(0.05f));
	m_nextMassPos.y = 1;
}

void Player::Update()
{
	// enemy の移動を考慮するため 入力、回転の外で行う。
	ChackTheNextMassFromMap();

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

	// カメラの向きから移動方向を決めるため、各向き事に違う処理を行う
	if (Input::Get().GetKeyStateTrigger(Button::Left))
	{
		m_angle = m_cameraMove->GetDirection();
		m_angle = Math::Vector2(m_angle.y, m_angle.x);
	}
	if (Input::Get().GetKeyStateTrigger(Button::Right))
	{
		m_angle = m_cameraMove->GetDirection() * -1.f;
		m_angle = Math::Vector2(m_angle.y, m_angle.x);
	}
	if (Input::Get().GetKeyStateTrigger(Button::Up))
	{
		m_angle = m_cameraMove->GetDirection();
		if (m_cameraMove->GetDirection().x != 0) m_angle.x *= -1.f;
	}
	if (Input::Get().GetKeyStateTrigger(Button::Down))
	{
		m_angle = m_cameraMove->GetDirection() * -1.f;
		if (m_cameraMove->GetDirection().x != 0) m_angle.x *= -1.f;
	}

	if (IsInput())
	{
		m_nextMassPos.x += -m_angle.x;
		m_nextMassPos.z +=  m_angle.y;
		m_nextMassPos.y = m_massPos.y;
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

	// 高さにずれが生じるため 0 を外す
	// 0 を考慮する場合は、下記コードを修正する必要がある。しかし、player 挙動があまり変わらないため実装しないと思う。
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
	case STONE: break;
	case SCISSORS: break;
	case PAPER: break;
	case NONE: break;
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
		case MassType::ITEM: HitItem(nextMass); break;
		case MassType::MESSEGE: HitMessege(nextMass); break;
		default: break;
		}
	}
}

void Player::HitItem(IMass* hitMass) noexcept
{
	if (isGetItem[GetNowBottomSurface()])
	{
		// game over
	}
	else
	{
		isGetItem[GetNowBottomSurface()] = true;
	}
}

void Player::HitMessege(IMass* hitMass) noexcept
{
	auto messege = dynamic_cast<Message*>(hitMass);
	messege->SetDrawMode(true);
}

void Player::HitEnemy(IMass* hitMass) noexcept
{

}

void Player::RotationWorld(const Math::Vector3& angle) noexcept
{
	auto mat = m_transform.GetLocalMatrix();

	// 回転行列のみの情報にするため
	mat *= (1.f / m_transform.GetScale().x);

	mat *= Math::Matrix::CreateRotation(angle);

	m_transform.SetRotation(mat.GetEulerAngles());
}

void Player::FinishRolling() noexcept
{
	m_angle = Math::Vector2();
	m_angleCount = 0;
	m_massPos = m_nextMassPos;
}

BOX_FACE_INFO Player::GetNowBottomSurface() noexcept
{
	auto right = m_transform.GetRight();
	auto up = m_transform.GetUp();
	auto forward = m_transform.GetForward();

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

	right *= -1.f;
	up *= -1.f;
	forward *= -1.f;

	if (abs(right.y + 1.f) <= 0.001f)
	{
		return BOX_FACE_INFO::NEGATIVE_X;
	}
	if (abs(up.y + 1.f) <= 0.001f)
	{
		return BOX_FACE_INFO::NEGATIVE_Y;
	}
	if (abs(forward.y + 1.f) <= 0.001f)
	{
		return BOX_FACE_INFO::NEGATIVE_Z;
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