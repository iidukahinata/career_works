/**
* @file    AudioListener.cpp
* @brief
*
* @date	   2022/05/09 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "AudioListener.h"
#include "Audio.h"

AudioListener::~AudioListener()
{
	Audio::Get().SetAudioListener(nullptr);
}

void AudioListener::Init(Transform* parent) noexcept
{
	m_parent = parent;

	Audio::Get().SetAudioListener(this);
}

FMOD_VECTOR AudioListener::GetPosition() const noexcept
{
	auto pos = m_parent->GetWoldPosition();
	return FMOD_VECTOR(pos.x, pos.y, pos.z);
}

FMOD_VECTOR AudioListener::GetForward() const noexcept
{
	auto forward = m_parent->GetForward();
	return FMOD_VECTOR(forward.x, forward.y, forward.z);
}

FMOD_VECTOR AudioListener::GetUp() const noexcept
{
	auto up = m_parent->GetUp();
	return FMOD_VECTOR(up.x, up.y, up.z);
}

void AudioListener::SetVelocity(const Math::Vector3& velocity) noexcept
{
	m_velocity = velocity;
}

FMOD_VECTOR AudioListener::GetVelocity() const noexcept
{
	return FMOD_VECTOR(m_velocity.x, m_velocity.y, m_velocity.z);
}