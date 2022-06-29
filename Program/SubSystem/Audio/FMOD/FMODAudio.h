/**
* @file    FMODAudio.h
* @brief
*
* @date	   2022/06/28 2022�N�x����
*/
#pragma once


#include <fmod.hpp>
#include "../Audio.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class FMODAudio : public Audio
{
	SUB_CLASS(FMODAudio)
public:

	FMODAudio();

	bool Initialize() override;
	void Shutdown() override;

	/** �S�Ă� 3D �T�E���h�̃O���[�o���ݒ��ύX���܂��B*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	void Update() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	class AudioListener* m_lisrener = nullptr;

	// * Audio Update �o�^�p
	Job m_job;
};