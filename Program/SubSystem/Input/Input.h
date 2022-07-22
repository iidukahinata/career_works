/**
 * @file	InputDevice.h
 * @brief   入力制御クラス
 *
 * @date	2022/07/19 2022年度初版
 */
#pragma once


#include "SubSystem/Core/ISubsystem.h"

namespace Button
{
	enum KeyAndMouse
	{
		// Mouse
		Lbutton,
		Rbutton,
		Mbutton,

		// Keyboard
		Back, Tab, Return, Pause, Escape, Space,
		Left, Up, Right, Down,
		Select, Delete, Help,

		A, B, C, D, E, F, G, H, I, J, K, L, N,
		M, O, P, Q, R, S, T, U, V, W, X, Y, Z,

		Lwin, Rwin, Apps, Sleep = 0x5F,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		Lshift, Rshift, Lcontrol, Rcontrol, Lmenu, Rmenu, Home, End,
		
		Max,
	};
}

/**
* Input抽象クラス
* このクラスではインターフェースのみを実装。
* 派生クラスで初期化等の関数を実装する。
*/
class Input : public ISubsystem
{
	SUB_CLASS(Input)
public:

	virtual bool Initialize() override { return true; }
	virtual void Shutdown() override {}

	/** マウス位置をスクリーン座標で返します */
	const Math::Vector2& GetMousePosition() const noexcept;

	/** マウス表示を管理します */
	void ShowMouse(bool show) const noexcept;

protected:

	/** 
	* Event Set 関数。
	* この関数を呼び出すことで、InputEventをEventManagerに登録し処理します。
	* 各派生Inputクラスではこの関数を使用しEventを知らせます。
	*/
	void PressKey(Button::KeyAndMouse id) const noexcept;
	void ReleaseKey(Button::KeyAndMouse id) const noexcept;

protected:

	// 任意キーが押されているかを保持
	Array<bool, Button::KeyAndMouse::Max> m_previousKeyState;
};