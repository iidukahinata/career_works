/**
* @file    Audio.h
* @brief
*
* @date	   2022/05/10 2022�N�x����
* @author  �ђ˗z��
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

	/* �S�Ă� 3D �T�E���h�̃O���[�o���ݒ��ύX���܂��B*/
	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) const noexcept;

	/* 3D �T�E���h���g�p����ꍇ�͕K���l���Z�b�g����K�v������܂��B*/
	void SetAudioListener(class AudioListener* listener) noexcept;

	FMOD::System* GetSystem() const noexcept;

private:

	FMOD::System* m_system = nullptr;

	class AudioListener* m_lisrener = nullptr;
};