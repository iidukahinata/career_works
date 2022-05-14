/**
* @file    Audio.cpp
* @brief
*
* @date	   2022/05/10 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "Audio.h"
#include "AudioHelper.h"
#include "AudioListener.h"

Audio::~Audio()
{
	Release();
}

bool Audio::Init(int maxChannel) noexcept
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_system);
	AUDIO_EORROR_CHECK(result);

	result = m_system->init(maxChannel, FMOD_INIT_NORMAL, nullptr);
	AUDIO_EORROR_CHECK(result);

	return true;
}

void Audio::Update() const noexcept
{
	FMOD_RESULT result;

	if (m_lisrener)
	{
		auto pos = m_lisrener->GetPosition();
		auto forward = m_lisrener->GetForward();
		auto up = m_lisrener->GetUp();
		auto velocity = m_lisrener->GetVelocity();

		result = m_system->set3DListenerAttributes(0, &pos, &forward, &up, &velocity);
		AUDIO_EORROR_CHECK(result);
	}

	result = m_system->update();
	AUDIO_EORROR_CHECK(result);
}

void Audio::Release() const noexcept
{
	m_system->close();
	m_system->release();
}

void Audio::Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept
{
	auto result = m_system->set3DSettings(dopplerscale, distancefactor, rolloffscale);
	AUDIO_EORROR_CHECK(result);
}

void Audio::SetAudioListener(AudioListener* const listener) noexcept
{
	m_lisrener = listener;
}

FMOD::System* Audio::GetSystem() const noexcept
{
	return m_system;
}