/**
* @file    FMODAudio.h
* @brief
*
* @date	   2022/06/28 2022年度初版
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

	/** 全ての 3D サウンドのグローバル設定を変更します。*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	void Update() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	class AudioListener* m_lisrener = nullptr;

	// * Audio Update 登録用
	Job m_job;
};