/**
* @file    RenderCommandFance.h
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/
#pragma once


#include <wrl/client.h>

/**
* GameThread ���� RenderingCommand �ǐ՗p�N���X
*/
class RenderCommandFance
{
public:

	RenderCommandFance();
	~RenderCommandFance();

	/** Fance �R�}���h�̒ǉ� */
	void BegineFrame() noexcept;

	/** Fance �R�}���h���S�ď��������܂őҋ@ */
	void WaitForSingle() const noexcept;

private:

	// * �ǉ�����Ă��� Fance �J�E���g
	std::atomic_uint32_t m_fanceValue;

	// * �҂��Ŏg�p����铯���C�x���g
	HANDLE m_hEvent;
};