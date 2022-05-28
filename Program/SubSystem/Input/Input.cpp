/**
* @file    Input.cpp
* @brief   ���͐���N���X
*
* @date	   2022/05/14 2022�N�x����
* @author  �ђ˗z��
*/


#include "Input.h"
#include "SubSystem/Window/Window.h"


void Input::Init()
{}

void Input::Update()
{
	m_previousKeyState = m_currentKeyState;

	// key���X�V
	for (auto& key : m_currentKeyState)
	{
		key.second = GetAsyncKeyState(key.first) & 0x8000;
	}

	// �}�E�X���W�X�V
	POINT mousePos = {};
	GetCursorPos(&mousePos);
	ScreenToClient(Window::Get().GetHandle(), &mousePos);
	m_mousePosition.x = mousePos.x;
	m_mousePosition.y = mousePos.y;
}

void Input::AddKeyState(Button::KeyAndMouse id) noexcept
{
	// ����ID���d�����Ȃ��悤��
	if (!m_currentKeyState.contains(id)) 
	{
		m_currentKeyState.emplace(id, false);
	}
}

bool Input::GetKeyStatePress(Button::KeyAndMouse id) noexcept
{
	// �z��O�ɃA�N�Z�X���Ȃ����߂̏���
	if (m_currentKeyState.contains(id))
	{
		return m_currentKeyState[id];
	}
	else 
	{
		// �܂�ID�w�肳���\��������̂Œǉ����Ă���
		AddKeyState(id);
		return false;
	}
}

bool Input::GetKeyStateTrigger(Button::KeyAndMouse id) noexcept
{
	// �z��O�ɃA�N�Z�X���Ȃ����߂̏���
	if (m_currentKeyState.contains(id))
	{
		return m_currentKeyState[id] && !m_previousKeyState[id];
	}
	else
	{
		// �܂�ID�w�肳���\��������̂Œǉ����Ă���
		AddKeyState(id);
		return false;
	}
}

void Input::ShowMouse(bool isShow) const noexcept
{
	ShowCursor(isShow);
}

const Math::Vector2& Input::GetMousePosition() const noexcept
{
	return m_mousePosition;
}