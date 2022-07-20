/**
 * @file	WinAPIInput.h
 * @brief   入力制御クラス
 *
 * @date	2022/07/19 2022年度初版
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

	/** 入力イベントチェックを行う。*/
	void Update() noexcept;

private:

	// * Input Update 登録用
	Job m_job;
};