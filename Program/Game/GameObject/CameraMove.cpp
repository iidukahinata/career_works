/**
* @file    CameraMove.cpp
* @brief
*
* @date	   2022/06/10 2022年度初版
* @author  飯塚陽太
*/


#include "CameraMove.h"
#include "../GameObject/Player.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"

void CameraMove::Init()
{
	player = m_scene->GetGameObject<Player>("player");

	if (auto camera = m_scene->GetMainCamera())
	{
		camera->GetTransform().SetPearent(this);
	}
}

void CameraMove::Update()
{
	if (player->IsGameClear())
	{
		m_transform.SetPosition(player->GetTransform().GetWoldPosition());
	}
	else
	{
		auto nextPos = player->GetTransform().GetWoldPosition();
		nextPos.y = m_transform.GetWoldPosition().y;
		m_transform.SetPosition(nextPos);
	}

	// 入力されたタイミングで、回転し始める。
	if (Input::Get().GetKeyStateTrigger(Button::SPACE) || m_rotateCount > 0)
	{
		if (m_rotateCount == 0)
		{
			m_directionID = static_cast<DIRECTION>((m_directionID + 1) % 4);
		}

		RotationY90Degree();
	}
}

const char* CameraMove::GetName()
{
	return "cameraMove";
}

Math::Vector2 CameraMove::GetDirection() noexcept
{
	switch (m_directionID)
	{
	case DIRECTION::DOWN:  return Math::Vector2::Down;
	case DIRECTION::LEFT:  return Math::Vector2::Left;
	case DIRECTION::UP:	   return Math::Vector2::Up;
	case DIRECTION::RIGHT: return Math::Vector2::Right;
	default: break;
	}
	return Math::Vector2();
}

void CameraMove::RotationY90Degree() noexcept
{
	m_rotateCount += m_rotateSpeed;
	if (m_rotateCount >= 90)
	{
		FinishRotation();
	}

	constexpr float rad = Math::ToRadian(1.f);
	auto rot = m_transform.GetRotation();
	rot.y += rad * static_cast<float>(m_rotateSpeed);
	m_transform.SetRotation(rot);
}

void CameraMove::FinishRotation() noexcept
{
	m_rotateCount = 0;

	// 360 度の範囲に合わせる。
	constexpr float rad = Math::ToRadian(360.f);
	auto rot = m_transform.GetRotation();
	if (rot.y > rad)
	{
		rot.y -= rad;
		m_transform.SetRotation(rot);
	}
}