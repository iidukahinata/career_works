/**
* @file    Audio.h
* @brief
*
* @date	   2022/06/23 2022年度初版
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

	/* 全ての 3D サウンドのグローバル設定を変更します。*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	/* 3D サウンドを使用する場合は必ず値をセットする必要があります。*/
	void SetAudioListener(class AudioListener* listener) noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	void Update() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	class AudioListener* m_lisrener = nullptr;

	/* Audio Update 登録用 */
	Job m_job;
};