/**
* @file		AudioClip.cpp
* @brief
*
* @date		2022/07/06 2022�N�x����
*/


#include "AudioClip.h"
#include "SubSystem/Audio/FMOD/FMODAudio.h"
#include "SubSystem/Audio/AudioHelper.h"

AudioClip::~AudioClip()
{
	if (m_channel)
	{
		Stop();
	}
	if (m_sound)
	{
		Release();
	}
}

void AudioClip::Play(FMOD::ChannelGroup* channelgroup /* = nullptr */) noexcept
{
	ASSERT(m_sound);

	auto result = m_audio->GetSystem()->playSound(m_sound, channelgroup, false, &m_channel);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::Pause() const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setPaused(true);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::UnPause() const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setPaused(false);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::Stop() noexcept
{
	ASSERT(m_channel);

	if (!IsPlaying())
		return;

	auto result = m_channel->stop();
	AUDIO_EORROR_CHECK(result);

	m_channel = nullptr;
}

void AudioClip::SetVolume(float volume) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setVolume(volume);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetPitch(float pitch) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setPitch(pitch);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetPan(float pan) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setPan(pan);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMute(bool mute) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setMute(mute);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMinMaxDistance(float min, float max) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->set3DMinMaxDistance(min, max);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetAttributes(const FMOD_VECTOR& pos, const FMOD_VECTOR& vel) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->set3DAttributes(&pos, &vel);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMixOutput(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setMixLevelsOutput(
		frontleft, frontright,
		center, lfe,
		surroundleft, surroundright,
		backleft, backright
	);

	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetPriority(int priority) const noexcept
{
	ASSERT(m_sound);

	float frequency;
	int unused;
	auto result = m_sound->getDefaults(&frequency, &unused);
	AUDIO_EORROR_CHECK(result);

	SetDefaults(frequency, priority);
}

void AudioClip::SetDefaults(float frequency, int priority) const noexcept
{
	ASSERT(m_sound);

	auto result = m_sound->setDefaults(frequency, priority);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMode(FMOD_MODE mode) const noexcept
{
	ASSERT(m_channel);

	auto result = m_channel->setMode(mode);
	AUDIO_EORROR_CHECK(result);
}

bool AudioClip::IsPlaying() const noexcept
{
	ASSERT(m_channel);

	bool isPlaying;
	auto result = m_channel->isPlaying(&isPlaying);

	// �������I�����Ă��鎞���G���[�����Ԃ���邽��
	if (result != FMOD_ERR_INVALID_HANDLE)
	{
		AUDIO_EORROR_CHECK(result);
	}
	return isPlaying;
}

void AudioClip::Release() const noexcept
{
	ASSERT(m_sound);

	auto result = m_sound->release();
	AUDIO_EORROR_CHECK(result);
}

bool AudioClip::Do_Load(StringView filePath) noexcept
{
	m_audio = dynamic_cast<FMODAudio*>(GetContext()->GetSubsystem<Audio>());

	ASSERT(m_audio);

	auto result = m_audio->GetSystem()->createSound(filePath.data(), FMOD_3D | FMOD_LOOP_NORMAL, nullptr, &m_sound);
	
	if (result != FMOD_OK) 
	{
		AUDIO_EORROR_CHECK(result);
		return false;
	}
	return true;
}