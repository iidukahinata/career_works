/**
* @file    CameraMove.cpp
* @brief
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "CameraMove.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"

void CameraMove::Init()
{
	player = m_scene->GetGameObject("player");

	if (auto camera = m_scene->GetMainCamera())
	{
		camera->GetTransform().SetPearent(this);
	}
}

void CameraMove::Update()
{
	m_transform.SetPosition(player->GetTransform().GetWoldPosition());

	// ���͂��ꂽ�^�C�~���O�ŁA��]���n�߂�B
	if (Input::Get().GetKeyStateTrigger(Button::SPACE) || m_rotateCount > 0)
	{
		RotationY90Degree();
	}
}

const char* CameraMove::GetName()
{
	return "cameraMove";
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
	rot.y += rad;
	m_transform.SetRotation(rot);
}

void CameraMove::FinishRotation() noexcept
{
	m_rotateCount = 0;

	// 360 �x�͈̔͂ɍ��킹��B
	constexpr float rad = Math::ToRadian(360.f);
	auto rot = m_transform.GetRotation();
	if (rot.y > rad)
	{
		rot.y -= rad;
		m_transform.SetRotation(rot);
	}
}