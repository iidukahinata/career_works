/**
 * @file	Timer.h
 * @brief   �t���[���Ǘ��N���X
 *
 * @date	2022/06/25 2022�N�x����
 */
#pragma once


#include <chrono>
#include "SubSystem/Core/ISubsystem.h"

 /**
 * �σt���[�����[�g�Ő���o����N���X
 */
class Timer : public ISubsystem
{
	SUB_CLASS(Timer)
public:

	bool Initialize() override;

	/**
	* �o�ߎ��Ԃ���t���[���̏�Ԃ�Ԃ�
	* mainLoop �̐擪�Ŏg�p�����悤�ɐ݌v����Ă���
	* @return true �̏ꍇ�� �t���[�� �̍X�V���}
	* @note
	*   2022/04/24���_�ł͐��x�������邽�߁A�o�ߎ��Ԃ���sleep_for�ł̑҂����������Ă��Ȃ��B
	*/
	bool ReachedNextFrame() noexcept;

	/** ���f���ꂽ�A�v���P�[�V�����ĊJ���Ɏ��Ԓ����̂��߂Ɏg�p����� */
	void ResetMeasurement() noexcept;

	/**
	* �ݒ蒆�� FPS �l �ύX���鎞�Ɏg�p
	* @param fps [����] �ύX��FPS�l���w��B
	*					0 �ȉ��̒l���w�肳�ꂽ�ꍇ�͏�������Ȃ�
	*/
	void SetFPS(float fps) noexcept;

	/** �Ō�� ReachedNextFrame �֐��ōX�V���ꂽ���_�̌o�ߎ��Ԃ�Ԃ� */
	double GetDeltaTime() const noexcept;

private:

	// * �ŐV�t���[���X�V����
	std::chrono::high_resolution_clock::time_point m_previousTime;

	// * �t���[���o�ߎ���(�b)
	double m_deltaTime;

	// * �ݒ蒆��FPS�l��b�ɕϊ������l
	double m_fpsTime;
};