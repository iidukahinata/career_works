/**
* @file    InputEvents.h
* @brief   ���͊֌W�̃C�x���g�N���X��`
*
* @date	   2022/06/23 2022�N�x����
*/
#pragma once


#include "InputHelper.h"

class KeyPressed : public IEvent
{
	SUB_CLASS(KeyPressed)
public:

	KeyPressed(Button::KeyAndMouse key);
	std::any GetData() override;

private:

	Button::KeyAndMouse m_key;
};

class KeyReleased : public IEvent
{
	SUB_CLASS(KeyReleased)
public:

	KeyReleased(Button::KeyAndMouse key);
	std::any GetData() override;

private:

	Button::KeyAndMouse m_key;
};