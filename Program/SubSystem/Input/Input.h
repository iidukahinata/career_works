/**
 * @file	InputDevice.h
 * @brief   ���͐���N���X
 *
 * @date	2022/07/19 2022�N�x����
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
* Input���ۃN���X
* ���̃N���X�ł̓C���^�[�t�F�[�X�݂̂������B
* �h���N���X�ŏ��������̊֐�����������B
*/
class Input : public ISubsystem
{
	SUB_CLASS(Input)
public:

	virtual bool Initialize() override { return true; }
	virtual void Shutdown() override {}

	/** �}�E�X�ʒu���X�N���[�����W�ŕԂ��܂� */
	const Math::Vector2& GetMousePosition() const noexcept;

	/** �}�E�X�\�����Ǘ����܂� */
	void ShowMouse(bool show) const noexcept;

protected:

	/** 
	* Event Set �֐��B
	* ���̊֐����Ăяo�����ƂŁAInputEvent��EventManager�ɓo�^���������܂��B
	* �e�h��Input�N���X�ł͂��̊֐����g�p��Event��m�点�܂��B
	*/
	void PressKey(Button::KeyAndMouse id) const noexcept;
	void ReleaseKey(Button::KeyAndMouse id) const noexcept;

protected:

	// �C�ӃL�[��������Ă��邩��ێ�
	Array<bool, Button::KeyAndMouse::Max> m_previousKeyState;
};