/**
 * @file	InputDevice.h
 * @brief   ���͐���N���X
 *
 * @date	2022/07/19 2022�N�x����
 */
#pragma once


#include "InputHelper.h"
#include "SubSystem/Core/ISubsystem.h"

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
	virtual const Math::Vector2& GetMousePosition() const noexcept;

	/** �}�E�X�\�����Ǘ����܂� */
	virtual void ShowMouse(bool show) const noexcept;

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