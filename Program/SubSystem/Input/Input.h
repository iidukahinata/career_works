/**
 * @file	InputDevice.h
 * @brief   ���͐���N���X
 *
 * @date	2022/05/14 2022�N�x����
 * @author	�ђ˗z��
 */
#pragma once


#include <map>
#include "SubSystem/Math/Vector2.h"

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

class Input
{
private:

	Input() = default;
	virtual ~Input() = default;
	Input(const Input&) = default;
	Input& operator=(const Input&) = default;

public:

	static Input& Get() noexcept
	{
		static Input instance;
		return instance;
	}

	void Init();
	void Update();

	/** ���̊֐����g�p���Ȃ��Ă��{�^���͒ǉ������ */
	void AddKeyState(Button::KeyAndMouse id) noexcept;

	/** ���w��{�^����������Ă��邩��Ԃ� */
	bool GetKeyStatePress(Button::KeyAndMouse id) noexcept;

	/** ���̎w��{�^���������ꂽ����Ԃ� */
	bool GetKeyStateTrigger(Button::KeyAndMouse id) noexcept;

	/** �}�E�X�ʒu���X�N���[�����W�ŕԂ��܂� */
	const Math::Vector2& GetMousePosition() const noexcept;

	/** �}�E�X�\�����Ǘ����܂� */
	void ShowMouse(bool show) const noexcept;

private:

	// Type -> <�L�[ID�A�����ꂽ��>
	std::map<Button::KeyAndMouse, bool> m_currentKeyState;
	std::map<Button::KeyAndMouse, bool> m_previousKeyState;

	// �X�N���[�����W�l�̃}�E�X�ʒu
	Math::Vector2 m_mousePosition;
};