/**
* @file    TitlePlayer.cpp
* @brief
*
* @date	   2022/06/06 2022年度初版
* @author  飯塚陽太
*/


#include "TitlePlayer.h"
#include "TitleString.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Timer/Timer.h"

#include "Game/Scene/SelectScene.h"

void TitlePlayer::Init()
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

	m_titleString = dynamic_cast<TitleString*>(m_scene->GetGameObject("TitleString"));

	m_transform.SetPosition(Math::Vector3(0.f, -10.f, 0.f));
	m_transform.SetScale(Math::Vector3(0.1f));
}

void TitlePlayer::Update()
{
	switch (m_animMode)
	{
	case AnimMode::ScreenIn: ScreenInAnimUpdate(); break;
	case AnimMode::Rotation: RotationAnimUpdate(); break;
	case AnimMode::ScreenOut: ScreenOutAnimUpdate(); break;
	case AnimMode::None: break;
	default: break;
	}
}

void TitlePlayer::Draw()
{
	m_model.Draw(m_transform.GetWorldMatrixXM());
}

const char* TitlePlayer::GetName()
{
	return "TitlePlayer";
}

void TitlePlayer::StartScreenOutAnim() noexcept
{
	m_animMode = AnimMode::ScreenOut;
	m_speed = -2.f;

	m_titleString->StartFadeOutAnim();
}

void TitlePlayer::ScreenInAnimUpdate() noexcept
{
	if (m_titleString->GetAnimMode() == TitleString::AnimMode::None)
	{
		auto pos = m_transform.GetPosition() + Math::Vector3(0.f, m_speed * Timer::Get().GetDeltaTime(), 0.f);
		m_transform.SetPosition(pos);

		if (pos.y > 0.f)
		{
			m_animMode = AnimMode::Rotation;
			m_speed = 1.f;

			pos.y = 0.f;
			m_transform.SetPosition(pos);

			m_titleString->StartUpDownAnim();
		}
	}
}

void TitlePlayer::ScreenOutAnimUpdate() noexcept
{
	auto pos = m_transform.GetPosition() + Math::Vector3(0.f, m_speed * Timer::Get().GetDeltaTime(), 0.f);
	m_transform.SetPosition(pos);

	m_speed += 0.5f;

	constexpr float maxSpeed = 15.f;
	m_speed > maxSpeed ? m_speed = maxSpeed : m_speed;

	if (pos.y > 8.f)
	{
		m_animMode = AnimMode::None;

		m_scene->GetSceneManager()->ChangeScene<SelectScene>();
	}
}

void TitlePlayer::RotationAnimUpdate() noexcept
{
	auto rot = m_transform.GetRotation() + Math::Vector3(0.f, Math::ToRadian(m_speed), 0.f);
	m_transform.SetRotation(rot);
}