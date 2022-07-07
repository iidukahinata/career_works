/**
* @file    FMODAudio.h
* @brief
*
* @date	   2022/07/08 2022年度初版
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

	/** 全ての 3D サウンドのグローバル設定を変更します。*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	void Update() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	// * Audio Update 登録用
	Job m_job;
};