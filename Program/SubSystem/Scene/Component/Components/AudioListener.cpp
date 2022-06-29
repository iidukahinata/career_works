/**
* @file    AudioListener.cpp
* @brief
*
* @date	   2022/06/29 2022�N�x����
*/


#include "AudioListener.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Audio/Audio.h"

void AudioListener::Initialize()
{
	m_audio = GetContext()->GetSubsystem<Audio>();

	RegisterToAudioSystem();
}

void AudioListener::Remove()
{
	UnRegisterFromAudioSystem();
}

void AudioListener::Active(bool active)
{
	IComponent::Active(active);
	if (active)
	{
		RegisterToAudioSystem();
	}
	else
	{
		UnRegisterFromAudioSystem();
	}
}

void AudioListener::SetVelocity(const Math::Vector3& velocity) noexcept
{
	m_velocity = velocity;
}

const Math::Vector3& AudioListener::GetVelocity() const noexcept
{
	return m_velocity;
}

void AudioListener::RegisterToAudioSystem()
{
	m_audio->SetAudioListener(this);
}

void AudioListener::UnRegisterFromAudioSystem()
{
	m_audio->SetAudioListener(nullptr);
}