/**
 * @file	InputDevice.h
 * @brief   入力制御クラス
 *
 * @date	2022/06/23 2022年度初版
 */
#pragma once


#include <map>
#include "SubSystem/Core/Math/Vector2.h"
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

namespace Button
{
	enum KeyAndMouse
	{
		// Mouse
		Lbutton = 0x01,
		Rbutton,
		Cancel,
		Mbutton,
		Xbutton1,
		Xbutton2,

		// Keyboard
		Back = 0x08, Tab,
		Clear = 0x0C, Return,
		Shift = 0x10, Control,
		Menu, Pause,
		Escape = 0x1B, SPACE = 0x20,
		Left = 0x25, Up, Right, Down,
		SEelect, Delete = 0x2E, Help,

		A = 0x41,
		B, C, D, E, F, G, H, I, J, K, L, N,
		M, O, P, Q, R, S, T, U, V, W, X, Y, Z,

		Lwin = 0x5B, Rwin, Apps, Sleep = 0x5F,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		Lshift = 0xA0, Rshift, Lcontrol, Rcontrol, Lmenu, Rmenu,
		Volume_Mute = 0xAD, Volume_Down, Volume_Up,
	};
}

class Input : public ISubsystem
{
	SUB_CLASS(Input)
public:

	Input();

	bool Initialize() override;
	void Shutdown() override;

	/** マウス位置をスクリーン座標で返します */
	const Math::Vector2& GetMousePosition() const noexcept;

	/** マウス表示を管理します */
	void ShowMouse(bool show) const noexcept;

private:

	void Update() noexcept;

	/** この関数を使用しなくてもボタンは追加される */
	void AddKey(Button::KeyAndMouse id) noexcept;

	/* Event Set 関数 */
	void PressKey(Button::KeyAndMouse id) const noexcept;
	void ReleaseKey(Button::KeyAndMouse id) const noexcept;

private:

	// Type -> <キーID、押されたか>
	std::map<Button::KeyAndMouse, bool> m_previousKeyState;

	/* Input Update 登録用 */
	Job m_job;
};