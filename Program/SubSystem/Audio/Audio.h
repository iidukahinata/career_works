/**
* @file    Audio.h
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <fmod.hpp>

class Audio
{
private:

	Audio() = default;
	Audio(const Audio&) = default;
	Audio& operator=(const Audio&) = default;

public:

	~Audio();

	static Audio& Get() noexcept
	{
		static Audio instance;
		return instance;
	}

	bool Init(int maxChannel) noexcept;
	void Update() const noexcept;
	void Release() const noexcept;

	/* 全ての 3D サウンドのグローバル設定を変更します。*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	/* 3D サウンドを使用する場合は必ず値をセットする必要があります。*/
	void SetAudioListener(class AudioListener* listener) noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	class AudioListener* m_lisrener = nullptr;
};