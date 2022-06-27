/**
 * @file	AudioSpeaker.cpp
 * @brief
 *
 * @date	2022/06/27 2022îNìxèâî≈
 */


#include "AudioSpeaker.h"

AudioSpeaker::~AudioSpeaker()
{
}

void AudioSpeaker::Update() noexcept
{

}

void AudioSpeaker::Play() noexcept
{

}

void AudioSpeaker::PlayOneShot(AudioClip* const clip, float volume /* = 1.f */) const noexcept
{

}

void AudioSpeaker::Pause() const noexcept
{

}

void AudioSpeaker::UnPause() const noexcept
{

}

void AudioSpeaker::Stop() noexcept
{

}

void AudioSpeaker::SetParent(Transform* const parent) noexcept
{

}

void AudioSpeaker::SetAudioClip(AudioClip* const pAudioClip, bool playOnAwake /* = false */) noexcept
{

}

void AudioSpeaker::SetMute(bool mute) noexcept
{

}

void AudioSpeaker::SetIsLoop(bool isLoop) noexcept
{

}

void AudioSpeaker::SetPriority(int priority) noexcept
{

}

void AudioSpeaker::SetVolume(float volume) noexcept
{

}

void AudioSpeaker::SetPitch(float pitch) noexcept
{

}

void AudioSpeaker::SetPan(float pan) noexcept
{

}

void AudioSpeaker::SetIs2DMode(bool is2DMode) noexcept
{

}

void AudioSpeaker::SetMaxDistance(float max) noexcept
{

}

void AudioSpeaker::SetOutPutMatrix(float* matrix, int size) noexcept
{

}

void AudioSpeaker::SetOutPutMatrix(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) noexcept
{

}

void AudioSpeaker::MakeAudioSettingsTheSame(AudioClip* const clip) const noexcept
{

}

FMOD_MODE AudioSpeaker::GetModeFromSettings() const noexcept
{
	return FMOD_MODE();
}