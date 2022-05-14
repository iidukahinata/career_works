/**
* @file		AudioClip.h
* @brief
*
* @date		2022/05/10 2022年度初版
* @author	飯塚陽太
*/
#pragma once


#include <fmod.hpp>
#include "../IResource.h"

/**
* オーディオ再生するたびに、呼び出し側で Channel 設定を変更する必要がある。
* AudioClip のみでの使用も可能だが、AudioSpeaker と併用しての使用を推奨。
*/
class AudioClip : public IResource
{
public:

	~AudioClip();

	void Play(FMOD::ChannelGroup* channelgroup = nullptr) noexcept;
	void Pause() const noexcept;
	void UnPause() const noexcept;
	void Stop() noexcept;

	/** Audio Channel 設定 */
	void SetMute(bool mute) const noexcept;
	void SetVolume(float volume) const noexcept;
	void SetPitch(float pitch) const noexcept;
	void SetPan(float pan) const noexcept;
	void SetMinMaxDistance(float min, float max) const noexcept;
	void SetAttributes(const FMOD_VECTOR& pos, const FMOD_VECTOR& vel) const noexcept;
	void SetMixOutput(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) const noexcept;

	/* Audio Sound 設定 */
	void SetPriority(int priority) const noexcept;
	void SetDefaults(float frequency, int priority) const noexcept;
	void SetMode(FMOD_MODE mode) const noexcept;

	bool IsPlaying() const noexcept;

private:

	void Release() const noexcept;

	// IResource
	bool Do_Load(std::string_view filePath) noexcept;

private:

	//* サウンドデータを保持。
	FMOD::Sound* m_sound = nullptr;

	//* サウンド設定を変更時に使用。サウンド再生中のみオブジェクトを保持する。
	FMOD::Channel* m_channel = nullptr;
};