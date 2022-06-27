/**
* @file    AudioListener.cpp
* @brief
*
* @date	   2022/06/27 2022îNìxèâî≈
*/


#include "AudioListener.h"

AudioListener::~AudioListener()
{

}

FMOD_VECTOR AudioListener::GetPosition() const noexcept
{
	return FMOD_VECTOR();
}

FMOD_VECTOR AudioListener::GetForward() const noexcept
{
	return FMOD_VECTOR();
}

FMOD_VECTOR AudioListener::GetUp() const noexcept
{
	return FMOD_VECTOR();
}

void AudioListener::SetVelocity(const Math::Vector3& velocity) noexcept
{
	m_velocity = velocity;
}

FMOD_VECTOR AudioListener::GetVelocity() const noexcept
{
	return FMOD_VECTOR(m_velocity.x, m_velocity.y, m_velocity.z);
}