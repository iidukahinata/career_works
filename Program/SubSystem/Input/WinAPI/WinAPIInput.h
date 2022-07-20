/**
 * @file	WinAPIInput.h
 * @brief   ���͐���N���X
 *
 * @date	2022/07/19 2022�N�x����
 */
#pragma once


#include "../Input.h"

class WinAPIInput : public Input
{
	SUB_CLASS(WinAPIInput)
public:

	WinAPIInput();

	bool Initialize() override;
	void Shutdown() override;

private:

	/** ���̓C�x���g�`�F�b�N���s���B*/
	void Update() noexcept;

private:

	// * Input Update �o�^�p
	Job m_job;
};