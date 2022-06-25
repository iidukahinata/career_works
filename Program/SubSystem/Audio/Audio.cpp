/**
* @file    Audio.cpp
* @brief
*
* @date	   2022/06/23 2022”N“x‰”Å
*/


#include "Audio.h"
#include "AudioHelper.h"
#include "Subsystem/Scene/Component/Components/AudioListener.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"

Audio::Audio()
{
	m_job.SetFunction([this](double) { Update(); });
	JobSystem::Get().RegisterJob(&m_job, FunctionType::Update);
}

bool Audio::Initialize()
{
	auto maxChannel = 64;
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_system);
	AUDIO_EORROR_CHECK(result);

	result = m_system->init(maxChannel, FMOD_INIT_NORMAL, nullptr);
	AUDIO_EORROR_CHECK(result);
	return true;
}

void Audio::Shutdown()
{
	if (m_system)
	{
		m_system->close();
		m_system->release();
	}
}

void Audio::Update() const noexcept
{
	ASSERT(m_system);

	FMOD_RESULT result;

	// 3D Mode Žžˆ—
	if (m_lisrener)
	{
		//auto pos = m_lisrener->GetPosition();
		//auto forward = m_lisrener->GetForward();
		//auto up = m_lisrener->GetUp();
		//auto velocity = m_lisrener->GetVelocity();

		//result = m_system->set3DListenerAttributes(0, &pos, &forward, &up, &velocity);
		//AUDIO_EORROR_CHECK(result);
	}

	result = m_system->update();
	AUDIO_EORROR_CHECK(result);
}

void Audio::Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept
{
	ASSERT(m_system);
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