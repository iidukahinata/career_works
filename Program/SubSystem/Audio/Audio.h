/**
* @file    Audio.h
* @brief
*
* @date	   2022/06/28 2022�N�x����
*/
#pragma once


#include "SubSystem/Core/ISubsystem.h"

class AudioListener;

/**
* Audio���ۃN���X
* ���̃N���X�ł̓C���^�[�t�F�[�X�݂̂������B
* �h���N���X�ŏ��������̊֐�����������B
*/
class Audio : public ISubsystem
{
	SUB_CLASS(Audio)
public:

	virtual bool Initialize() override { return true; }
	virtual void Shutdown() override {}

	/** 3D �T�E���h���g�p����ꍇ�͕K���l���Z�b�g����K�v������܂��B*/
	void SetAudioListener(AudioListener* listener) noexcept;

protected:

	class AudioListener* m_lisrener = nullptr;
};