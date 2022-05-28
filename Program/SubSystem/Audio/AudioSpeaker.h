/**
* @file		AudioSpeaker.h
* @brief
*
* @date		2022/05/14 2022�N�x����
* @author	�ђ˗z��
*/
#pragma once


#include <fmod.hpp>
#include "SubSystem/Math/Vector3.h"

/**
* AudioClip �N���X�� 3D �����Aplay ���ݒ���Ǘ���������N���X�ł��B
* �܂� 3D �������g�p���Ȃ��T�E���h�̏ꍇ�́AAudioClip�ATransform ���Z�b�g����K�v�͂���܂���B
*
* @note
* 2022/05/09 ���_�ł͂��̃N���X�� ChannelGroup ���͖��g�p�̂��ߎ����͂��Ă��Ȃ��B
*/
class AudioSpeaker
{
public:

	/* 3D �������g�p���Ȃ��ꍇ�͋�֐��ɂȂ�܂��B*/
	void Update() noexcept;

	void Play() noexcept;
	void PlayOneShot(class AudioClip* clip, float volume = 1.f) const noexcept;
	void Pause() const noexcept;
	void UnPause() const noexcept;
	void Stop() noexcept;

	/* 3D �����Ŏg�p����� Transform ���Z�b�g���܂��B*/
	void SetParent(class Transform* parent) noexcept;

	void SetAudioClip(class AudioClip* clip, bool playOnAwake = false) noexcept;

	void SetMute(bool mute) noexcept;
	void SetIsLoop(bool isLoop) noexcept;

	/* 0 ����ԗD��x�������A�����l�� 0 ���� 256 �̊Ԃ� clamp ����܂��B */
	void SetPriority(int priority) noexcept;

	/* 1 ����ԉ����傫���A�����l�� 0 ���� 1 �̊Ԃ� clamp ����܂��B */
	void SetVolume(float volume) noexcept;

	/* 2 ����ԉ��������A�����l�� 0 ���� 2 �̊Ԃ� clamp ����܂��B */
	void SetPitch(float pitch) noexcept;

	/* 0 �����E�����o�����X�ɂȂ�A�����l�� -1 ���� 1 �̊Ԃ� clamp ����܂��B */
	void SetPan(float pan) noexcept;

	/* true �ɂ���� 3D �����𖳎����܂� */
	void SetIs2DMode(bool is2DMode) noexcept;

	/* 	�T�E���h�̌������~�����鋗�� */
	void SetMaxDistance(float max) noexcept;

	/* �X�s�[�J�[�̉����ʂŒ�������֐��ł��B */
	void SetOutPutMatrix(float* matrix, int size) noexcept;
	void SetOutPutMatrix(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright) noexcept;

private:

	void MakeAudioSettingsTheSame(class AudioClip* clip) const noexcept;
	FMOD_MODE GetModeFromSettings() const noexcept;

private:

	//* 3D ���������邽�߂Ɉʒu��񂪂Ђ悤�Ȃ��ߕێ��B2D �̏ꍇ�͖��g�p�B
	class Transform* m_parent = nullptr;

	//* ���g�̈ړ����x���t���[���ԍ������狁�߂邽�ߎg�p�B2D �̏ꍇ�͖��g�p�B
	Math::Vector3 m_oldPos;

	//* �ʒu���� 3D �����̒l�X�V�����B
	class AudioClip* m_audioClip = nullptr;

	//* Audio �ݒ�
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