/**
 * @file	AudioSpeaker.cpp
 * @brief
 *
 * @date	2022/06/09 2022年度初版
 * @author	飯塚陽太
 */


#include "AudioSpeaker.h"
#include "Audio.h"
#include "SubSystem/Resource/Resources/Audio/AudioClip.h"
#include "SubSystem/Scene/Transform.h"
#include "SubSystem/Core/Common/Common.h"

AudioSpeaker::~AudioSpeaker()
{
	if (m_audioClip)
	{
		m_audioClip->SubReneceCount();
	}
}

void AudioSpeaker::Update() noexcept
{
	ASSERT(m_parent);

	Math::Vector3 worldPos = m_parent->GetWoldPosition();
	Math::Vector3 velcity = worldPos - m_oldPos;

	if (m_audioClip)
	{
		FMOD_VECTOR pos = { worldPos.x, worldPos.y, worldPos.z };
		FMOD_VECTOR vel = { velcity.x, velcity.y, velcity.z };
		m_audioClip->SetAttributes(pos, vel);
	}

	m_oldPos = worldPos;
}

void AudioSpeaker::Play() noexcept
{
	ASSERT(m_audioClip);

	if (m_isPlaying)
		Stop();

	m_audioClip->Play();

	// thisの設定をaudioDateに渡す
	MakeAudioSettingsTheSame(m_audioClip);

	m_isPlaying = true;
}

void AudioSpeaker::PlayOneShot(AudioClip* const clip, float volume /* = 1.f */) const noexcept
{
	clip->Play();

	// thisの設定をaudioDateに渡す
	MakeAudioSettingsTheSame(clip);

	clip->SetVolume(volume);

	// 3D 時、初期値として再生位置をセット。
	if (m_is2DMode == false)
	{
		auto worldPos = m_parent ? m_parent->GetWoldPosition() : Math::Vector3::Zero;
		FMOD_VECTOR pos = { worldPos.x, worldPos.y, worldPos.z };
		FMOD_VECTOR vel = { 0, 0, 0 };
		clip->SetAttributes(pos, vel);
	}
}

void AudioSpeaker::Pause() const noexcept
{
	ASSERT(m_audioClip);

	m_audioClip->Pause();
}

void AudioSpeaker::UnPause() const noexcept
{
	ASSERT(m_audioClip);

	m_audioClip->UnPause();
}

void AudioSpeaker::Stop() noexcept
{
	ASSERT(m_audioClip);

	m_audioClip->Stop();
	m_isPlaying = false;
}

void AudioSpeaker::SetParent(Transform* const parent) noexcept
{
	m_parent = parent;
}

void AudioSpeaker::SetAudioClip(AudioClip* const pAudioClip, bool playOnAwake /* = false */) noexcept
{
	m_audioClip = pAudioClip;

	if (playOnAwake)
	{
		Play();
	}
}

void AudioSpeaker::SetMute(bool mute) noexcept
{
	m_mute = mute;
}

void AudioSpeaker::SetIsLoop(bool isLoop) noexcept
{
	m_isLoop = isLoop;
}

void AudioSpeaker::SetPriority(int priority) noexcept
{
	m_priority = std::clamp(m_priority, 0, 256);
}

void AudioSpeaker::SetVolume(float volume) noexcept
{
	m_volume = std::clamp(volume, 0.f, 1.f);
}

void AudioSpeaker::SetPitch(float pitch) noexcept
{
	m_pitch = std::clamp(pitch, 0.f, 2.f);
}

void AudioSpeaker::SetPan(float pan) noexcept
{
	m_pan = std::clamp(pan, -1.f, 1.f);
}

void AudioSpeaker::SetIs2DMode(bool is2DMode) noexcept
{
	m_is2DMode = is2DMode;
}

void AudioSpeaker::SetMaxDistance(float max) noexcept
{
	m_maxDistance = std::max(max, 1.f);
}

void AudioSpeaker::SetOutPutMatrix(float* matrix, int size) noexcept
{
	size = std::min(size, 8);
	for (int i = 0; i < size; ++i)
	{
		m_levelMatrix[i] = std::clamp(matrix[i], 0.f, 1.f);
	}
}

void AudioSpeaker::SetOutPutMatrix(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) noexcept
{
	m_levelMatrix[0] = frontleft;
	m_levelMatrix[1] = frontright;
	m_levelMatrix[2] = center;
	m_levelMatrix[3] = lfe;
	m_levelMatrix[4] = surroundleft;
	m_levelMatrix[5] = surroundright;
	m_levelMatrix[6] = backleft;
	m_levelMatrix[7] = backright;
}

void AudioSpeaker::MakeAudioSettingsTheSame(AudioClip* const clip) const noexcept
{
	clip->SetMixOutput(
		m_levelMatrix[0], m_levelMatrix[1], m_levelMatrix[2], m_levelMatrix[3],
		m_levelMatrix[4], m_levelMatrix[5], m_levelMatrix[6], m_levelMatrix[7]
	);

	clip->SetMute(m_mute);
	clip->SetPriority(m_priority);
	clip->SetVolume(m_volume);
	clip->SetPitch(m_pitch);
	clip->SetPan(m_pan);
	clip->SetMinMaxDistance(1.f, m_maxDistance);

	clip->SetMode(GetModeFromSettings());
}

FMOD_MODE AudioSpeaker::GetModeFromSettings() const noexcept
{
	FMOD_MODE mode = FMOD_DEFAULT;

	if (m_is2DMode) {
		mode |= FMOD_2D;
	}
	else {
		mode |= FMOD_3D;
	}

	if (m_isLoop) {
		mode |= FMOD_LOOP_NORMAL;
	}
	else {
		mode |= FMOD_LOOP_OFF;
	}

	return mode;
}