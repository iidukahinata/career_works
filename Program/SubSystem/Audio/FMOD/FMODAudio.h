/**
* @file    FMODAudio.h
* @brief
*
* @date	   2022/07/08 2022�N�x����
*/
#pragma once


#include "../Audio.h"

namespace FMOD
{
	class System;
}

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

	// * Audio Update �o�^�p
	Job m_job;
};