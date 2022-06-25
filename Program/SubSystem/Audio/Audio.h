/**
* @file    Audio.h
* @brief
*
* @date	   2022/06/23 2022�N�x����
*/
#pragma once


#include <fmod.hpp>
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class Audio : public ISubsystem
{
	SUB_CLASS(Audio)
public:

	Audio();

	bool Initialize() override;
	void Shutdown() override;

	/* �S�Ă� 3D �T�E���h�̃O���[�o���ݒ��ύX���܂��B*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	/* 3D �T�E���h���g�p����ꍇ�͕K���l���Z�b�g����K�v������܂��B*/
	void SetAudioListener(class AudioListener* listener) noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	void Update() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	class AudioListener* m_lisrener = nullptr;

	/* Audio Update �o�^�p */
	Job m_job;
};