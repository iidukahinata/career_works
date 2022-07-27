/**
 * @file	DirectInput.h
 * @brief
 *
 * @date	2022/07/19 2022年度初版
 */
#pragma once


#include <dinput.h>
#include <wrl/client.h>
#include "../Input.h"

class DirectInput : public Input
{
	SUB_CLASS(DirectInput)
public:

	DirectInput();

	bool Initialize() override;
	void Shutdown() override;

private:

	/** 入力イベントチェックを行う。*/
	void Update() noexcept;

	bool GetKeyBuffer() noexcept;
	bool GetMouseBuffer() noexcept;

	void ConvertMyInputData() noexcept;

private:

	Microsoft::WRL::ComPtr<IDirectInput8> m_directInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8>	m_directKeyboard;
	Microsoft::WRL::ComPtr<IDirectInputDevice8>	m_directMouse;

	Array<char, 256> m_keybuffer; // キーボードバッファ
	DIMOUSESTATE2 m_mouseState;   // マウスの状態

	// * Input Update 登録用
	Job m_job;
};