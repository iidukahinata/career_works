/**
* @file    AudioListener.cpp
* @brief
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/


#include "AudioListener.h"
#include "SubSystem/Audio/Audio.h"
#include "SubSystem/Core/Common/Tools.h"
#include "SubSystem/Core/Common/Common.h"

AudioListener::~AudioListener()
{
	//Audio::Get().SetAudioListener(nullptr);
}

//void AudioListener::Init(Transform* parent) noexcept
//{
//	m_parent = parent;
//
//	//Audio::Get().SetAudioListener(this);
//}

//FMOD_VECTOR AudioListener::GetPosition() const noexcept
//{
//	//ASSERT(m_parent, "このクラスは初期化されていません。");
//
//	auto pos = m_parent->GetWoldPosition();
//	return FMOD_VECTOR(pos.x, pos.y, pos.z);
//}

//FMOD_VECTOR AudioListener::GetForward() const noexcept
//{
//	//ASSERT(m_parent, "このクラスは初期化されていません。");
//
//	auto forward = m_parent->GetForward();
//	return FMOD_VECTOR(forward.x, forward.y, forward.z);
//}

//FMOD_VECTOR AudioListener::GetUp() const noexcept
//{
//	//ASSERT(m_parent, "このクラスは初期化されていません。");
//
//	//auto up = m_parent->GetUp();
//	//return FMOD_VECTOR(up.x, up.y, up.z);
//}

void AudioListener::SetVelocity(const Math::Vector3& velocity) noexcept
{
	m_velocity = velocity;
}

FMOD_VECTOR AudioListener::GetVelocity() const noexcept
{
	return FMOD_VECTOR(m_velocity.x, m_velocity.y, m_velocity.z);
}