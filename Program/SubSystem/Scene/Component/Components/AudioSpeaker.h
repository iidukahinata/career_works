/**
* @file		AudioSpeaker.h
* @brief
*
* @date		2022/07/06 2022年度初版
*/
#pragma once


#include "../IComponent.h"

class AudioClip;

class AudioSpeaker : public IComponent
{
	SUB_CLASS(AudioSpeaker)
public:

	void Initialize() override;
	void Remove() override;

	void Update(double deltaTime) override;

	void Play() noexcept;
	void PlayOneShot(AudioClip* clip, float volume = 1.f) const noexcept;
	void Pause() const noexcept;
	void UnPause() const noexcept;
	void Stop() noexcept;

	void SetAudioClip(AudioClip* clip, bool playOnAwake = false) noexcept;

	void SetMute(bool mute) noexcept;
	void SetIsLoop(bool isLoop) noexcept;

	/* 0 が一番優先度が高く、引数値は 0 から 256 の間に clamp されます。*/
	void SetPriority(int priority) noexcept;

	/* 1 が一番音が大きく、引数値は 0 から 1 の間に clamp されます。*/
	void SetVolume(float volume) noexcept;

	/* 2 が一番音が高く、引数値は 0 から 2 の間に clamp されます。*/
	void SetPitch(float pitch) noexcept;

	/* 0 が左右同じバランスになり、引数値は -1 から 1 の間に clamp されます。*/
	void SetPan(float pan) noexcept;

	/* true にすると 3D 処理を無視します。*/
	void SetIs2DMode(bool is2DMode) noexcept;

	/* 	サウンドの減衰を停止させる距離 */
	void SetMaxDistance(float max) noexcept;

	/* スピーカーの音を個別で調整する関数です。*/
	void SetOutPutMatrix(float* matrix, int size) noexcept;
	void SetOutPutMatrix(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) noexcept;

private:

	void MakeAudioSettingsTheSame(AudioClip* clip) const noexcept;
	uint32_t GetModeFromSettings() const noexcept;

private:

	// * 自身の移動速度をフレーム間差分から求めるため使用。2D の場合は未使用。
	Math::Vector3 m_oldPos;
	Math::Vector3 m_velocity;

	// * 位置等の 3D 処理の値更新される。
	AudioClip* m_audioClip = nullptr;

	// * Audio 設定
	bool  m_mute           = false;
	bool  m_isLoop         = false;
	int	  m_priority       = 128;
	float m_volume         = 1.f;
	float m_pitch          = 1.f;
	float m_pan            = 0.f;
	bool  m_is2DMode       = false;
	float m_maxDistance    = 10000;
	float m_levelMatrix[8] = {};

	bool m_isPlaying = false;
};