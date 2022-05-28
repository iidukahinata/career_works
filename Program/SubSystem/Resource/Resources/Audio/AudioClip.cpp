/**
* @file		AudioClip.cpp
* @brief
*
* @date		2022/05/28 2022�N�x����
* @author	�ђ˗z��
*/


#include "AudioClip.h"
#include "SubSystem/Audio/Audio.h"
#include "SubSystem/Audio/AudioHelper.h"
#include "SubSystem/Tools/Chack.h"


AudioClip::~AudioClip()
{
	Stop();
	Release();
}

void AudioClip::Play(FMOD::ChannelGroup* channelgroup /* = nullptr */) noexcept
{
	Chack(m_sound);

	auto result = Audio::Get().GetSystem()->playSound(m_sound, channelgroup, false, &m_channel);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::Pause() const noexcept
{
	Chack(m_channel);

	auto result = m_channel->setPaused(true);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::UnPause() const noexcept
{
	Chack(m_channel);

	auto result = m_channel->setPaused(false);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::Stop() noexcept
{
	Chack(m_channel);

	if (!IsPlaying())
		return;

	auto result = m_channel->stop();
	AUDIO_EORROR_CHECK(result);

	m_channel = nullptr;
}

void AudioClip::SetVolume(float volume) const noexcept
{
	Chack(m_channel);

	auto result = m_channel->setVolume(volume);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetPitch(float pitch) const noexcept
{
	Chack(m_channel);

	auto result = m_channel->setPitch(pitch);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetPan(float pan) const noexcept
{
	Chack(m_channel);

	auto result = m_channel->setPan(pan);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMute(bool mute) const noexcept
{
	Chack(m_channel);

	auto result = m_channel->setMute(mute);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMinMaxDistance(float min, float max) const noexcept
{
	Chack(m_channel);

	auto result = m_channel->set3DMinMaxDistance(min, max);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetAttributes(const FMOD_VECTOR& pos, const FMOD_VECTOR& vel) const noexcept
{
	Chack(m_channel);

	auto result = m_channel->set3DAttributes(&pos, &vel);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMixOutput(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) const noexcept
{
	Chack(m_channel);

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
	Chack(m_sound);

	float frequency;
	int unused;
	auto result = m_sound->getDefaults(&frequency, &unused);
	AUDIO_EORROR_CHECK(result);

	SetDefaults(frequency, priority);
}

void AudioClip::SetDefaults(float frequency, int priority) const noexcept
{
	Chack(m_sound);

	auto result = m_sound->setDefaults(frequency, priority);
	AUDIO_EORROR_CHECK(result);
}

void AudioClip::SetMode(FMOD_MODE mode) const noexcept
{
	Chack(m_sound);

	auto result = m_sound->setMode(mode);
	AUDIO_EORROR_CHECK(result);
}

bool AudioClip::IsPlaying() const noexcept
{
	Chack(m_channel);

	bool isPlaying;
	auto result = m_channel->isPlaying(&isPlaying);
	AUDIO_EORROR_CHECK(result);

	return isPlaying;
}

void AudioClip::Release() const noexcept
{
	Chack(m_sound);

	auto result = m_sound->release();
	AUDIO_EORROR_CHECK(result);
}

bool AudioClip::Do_Load(std::string_view filePath) noexcept
{
	auto result = Audio::Get().GetSystem()->createSound(filePath.data(), FMOD_3D, nullptr, &m_sound);

	if (result != FMOD_OK) 
	{
		AUDIO_EORROR_CHECK(result);
		return false;
	}
	return true;
}