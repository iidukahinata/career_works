/**
* @file		AudioSpeaker.h
* @brief
*
* @date		2022/05/14 2022年度初版
* @author	飯塚陽太
*/
#pragma once


#include <fmod.hpp>
#include "SubSystem/Math/Vector3.h"

/**
* AudioClip クラスの 3D 処理、play 時設定を管理処理するクラスです。
* また 3D 処理を使用しないサウンドの場合は、AudioClip、Transform をセットする必要はありません。
*
* @note
* 2022/05/09 時点ではこのクラスは ChannelGroup 等は未使用のため実装はしていない。
*/
class AudioSpeaker
{
public:

	/* 3D 処理を使用しない場合は空関数になります。*/
	void Update() noexcept;

	void Play() noexcept;
	void PlayOneShot(class AudioClip* clip, float volume = 1.f) const noexcept;
	void Pause() const noexcept;
	void UnPause() const noexcept;
	void Stop() noexcept;

	/* 3D 処理で使用される Transform をセットします。*/
	void SetParent(class Transform* parent) noexcept;

	void SetAudioClip(class AudioClip* clip, bool playOnAwake = false) noexcept;

	void SetMute(bool mute) noexcept;
	void SetIsLoop(bool isLoop) noexcept;

	/* 0 が一番優先度が高く、引数値は 0 から 256 の間に clamp されます。 */
	void SetPriority(int priority) noexcept;

	/* 1 が一番音が大きく、引数値は 0 から 1 の間に clamp されます。 */
	void SetVolume(float volume) noexcept;

	/* 2 が一番音が高く、引数値は 0 から 2 の間に clamp されます。 */
	void SetPitch(float pitch) noexcept;

	/* 0 が左右同じバランスになり、引数値は -1 から 1 の間に clamp されます。 */
	void SetPan(float pan) noexcept;

	/* true にすると 3D 処理を無視します */
	void SetIs2DMode(bool is2DMode) noexcept;

	/* 	サウンドの減衰を停止させる距離 */
	void SetMaxDistance(float max) noexcept;

	/* スピーカーの音を個別で調整する関数です。 */
	void SetOutPutMatrix(float* matrix, int size) noexcept;
	void SetOutPutMatrix(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) noexcept;

private:

	void MakeAudioSettingsTheSame(class AudioClip* clip) const noexcept;
	FMOD_MODE GetModeFromSettings() const noexcept;

private:

	//* 3D 処理させるために位置情報がひつようなため保持。2D の場合は未使用。
	class Transform* m_parent = nullptr;

	//* 自身の移動速度をフレーム間差分から求めるため使用。2D の場合は未使用。
	Math::Vector3 m_oldPos;

	//* 位置等の 3D 処理の値更新される。
	class AudioClip* m_audioClip = nullptr;

	//* Audio 設定
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