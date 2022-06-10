/**
* @file    TitlePlayer.cpp
* @brief
*
* @date	   2022/06/10 2022�N�x����
* @author  �ђ˗z��
*/


#include "TitlePlayer.h"
#include "TitleString.h"
#include "../Scene/SelectScene.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Resource/ResourceManager.h"

void TitlePlayer::Awake()
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

	m_audioClip = ResourceManager::Get().Load<AudioClip>("assets/Imqube/Wav/SE_YES2.wav");
}

void TitlePlayer::Init()
{
	m_titleString = dynamic_cast<TitleString*>(m_scene->GetGameObject("TitleString"));

	m_transform.SetPosition(Math::Vector3(0.f, -10.f, 0.f));
	m_transform.SetScale(Math::Vector3(0.1f));

	m_animator.RegisterAnimation("ScreenIn", [this] { ScreenInAnim(); });
	m_animator.RegisterAnimation("Rotation", [this] { RotationAnim(); });
	m_animator.RegisterAnimation("ScreenOut", [this] { ScreenOutAnim(); });

	m_animator.SetAnimation("ScreenIn");
	m_audioSpeaker.SetAudioClip(m_audioClip);
}

void TitlePlayer::Update()
{
	m_animator.Update();
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
	m_animator.SetAnimation("ScreenOut");
	m_speed = -2.f;

	m_audioSpeaker.Play();

	m_titleString->StartFadeOutAnim();
}

void TitlePlayer::ScreenInAnim() noexcept
{
	// �^�C�g���������\������Ă���A�j���[�V�������J�n���邽�߁B
	if (m_titleString->IsNoneAnim())
	{
		auto pos = m_transform.GetPosition() + Math::Vector3(0.f, m_speed * Timer::Get().GetDeltaTime(), 0.f);
		m_transform.SetPosition(pos);

		if (pos.y >= 0.f)
		{
			m_animator.SetAnimation("Rotation");

			pos.y = 0.f;
			m_transform.SetPosition(pos);

			m_titleString->StartUpDownAnim();
		}
	}
}

void TitlePlayer::ScreenOutAnim() noexcept
{
	auto pos = m_transform.GetPosition() + Math::Vector3(0.f, m_speed * Timer::Get().GetDeltaTime(), 0.f);
	m_transform.SetPosition(pos);

	m_speed += 0.75f;

	constexpr float maxSpeed = 20.f;
	m_speed > maxSpeed ? m_speed = maxSpeed : m_speed;

	if (pos.y > 8.f)
	{
		m_animator.StopAnimation();
		m_scene->GetSceneManager()->ChangeScene<SelectScene>();
	}
}

void TitlePlayer::RotationAnim() noexcept
{
	auto rot = m_transform.GetRotation() + Math::Vector3(0.f, Math::ToRadian(1.f), 0.f);
	m_transform.SetRotation(rot);
}