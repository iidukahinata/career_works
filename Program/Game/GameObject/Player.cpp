/**
* @file    Player.cpp
* @brief
*
* @date	   2022/06/09 2022年度初版
* @author  飯塚陽太
*/


#include "Player.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"
#include "Stage.h"
#include "Human.h"
#include "CameraMove.h"

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
	m_cameraMove = m_scene->GetGameObject<CameraMove>("cameraMove");
	m_stage = m_scene->GetGameObject<Stage>("stage");

	Math::Vector3 massPos(m_massPos.x, m_massPos.y, m_massPos.z);
	m_transform.SetPosition(Math::Vector3(0.75f * massPos.x, 0.75f * massPos.y, 0.75f * massPos.z));
	m_transform.SetScale(Math::Vector3(0.05f));

	m_animator.RegisterAnimation("GameClear", [this] { GameClearAnim(); });
	m_animator.RegisterAnimation("GameOver", [this] { GameOverAnim(); });
}

void Player::Update()
{
	if (m_hitStop.IsHitStop())
		return;

	// アニメーション中は game が終了しているため入力等を受け付けないようにするため
	if (!m_animator.IsPlaying())
	{
		// enemy の移動を考慮するため 入力、回転の外で行う。
		ChackTheNextMassFromStage();

		InputAction();

		Rolling();
	}
	else
	{
		m_animator.Update();
	}
}

void Player::Draw()
{
	// game over animation がないため描画しないことにする。
	if (IsGameOver())
	{
		return;
	}

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

	auto InuptLeft = [this] {
		m_angle = m_cameraMove->GetDirection();
		m_angle = Math::Vector2(m_angle.y, m_angle.x);
	};

	auto InuptRight = [this] {
		m_angle = -m_cameraMove->GetDirection();
		m_angle = Math::Vector2(m_angle.y, m_angle.x);
	};

	auto InuptUp = [this] {
		m_angle = m_cameraMove->GetDirection();
		if (m_cameraMove->GetDirection().x != 0) m_angle.x *= -1.f;
	};

	auto InuptDown = [this] {
		m_angle = -m_cameraMove->GetDirection();
		if (m_cameraMove->GetDirection().x != 0) m_angle.x *= -1.f;
	};

	// カメラの向きから移動方向を決めるため、各向き事に違う処理を行う
	if (Input::Get().GetKeyStatePress(Button::Left))
	{
		InuptLeft();
	}
	if (Input::Get().GetKeyStatePress(Button::Right))
	{
		InuptRight();
	}
	if (Input::Get().GetKeyStatePress(Button::Up))
	{
		InuptUp();
	}
	if (Input::Get().GetKeyStatePress(Button::Down))
	{
		InuptDown();
	}

	if (IsInput())
	{
		// 高さは考慮していない
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

	// 高さにずれが生じるため 0 を外す
	// player 移動を等加速度運動に変更する場合は、下記コードを修正する必要がある。
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
	case NONE: m_animator.SetAnimation("GameOver"); break;
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
	// 回転後に取得判定を入れるため
	if (IsInput())
	{
		return;
	}

	if (isGetHuman[GetNowBottomSurface()])
	{
		m_animator.SetAnimation("GameOver");
	}
	else
	{
		isGetHuman[GetNowBottomSurface()] = true;

		m_stage->RemoveMass(hitMass);
		m_scene->RemoveGameObject(hitMass);

		if(m_stage->IsClear())
		{
			m_animator.SetAnimation("GameClear");
		}
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
			m_animator.SetAnimation("GameOver");
		}
	}
	else
	{
		m_animator.SetAnimation("GameOver");
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

void Player::GameClearAnim() noexcept
{
	auto pos = m_transform.GetPosition();
	pos.y += 0.025f;
	m_transform.SetPosition(pos);

	RotationWorld(Math::Vector3(0.f, Math::ToRadian(10.f), 0.f));
}

void Player::GameOverAnim() noexcept
{

}

bool Player::IsGameOver() const noexcept
{
	return m_animator.GetCurrentAnimName() == "GameOver";
}

bool Player::IsGameClear() const noexcept
{
	return m_animator.GetCurrentAnimName() == "GameClear";
}