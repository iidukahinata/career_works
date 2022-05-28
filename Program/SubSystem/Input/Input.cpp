/**
* @file    Input.cpp
* @brief   入力制御クラス
*
* @date	   2022/05/14 2022年度初版
* @author  飯塚陽太
*/


#include "Input.h"
#include "SubSystem/Window/Window.h"


void Input::Init()
{}

void Input::Update()
{
	m_previousKeyState = m_currentKeyState;

	// key情報更新
	for (auto& key : m_currentKeyState)
	{
		key.second = GetAsyncKeyState(key.first) & 0x8000;
	}

	// マウス座標更新
	POINT mousePos = {};
	GetCursorPos(&mousePos);
	ScreenToClient(Window::Get().GetHandle(), &mousePos);
	m_mousePosition.x = mousePos.x;
	m_mousePosition.y = mousePos.y;
}

void Input::AddKeyState(Button::KeyAndMouse id) noexcept
{
	// 同じIDが重複しないように
	if (!m_currentKeyState.contains(id)) 
	{
		m_currentKeyState.emplace(id, false);
	}
}

bool Input::GetKeyStatePress(Button::KeyAndMouse id) noexcept
{
	// 配列外にアクセスしないための処理
	if (m_currentKeyState.contains(id))
	{
		return m_currentKeyState[id];
	}
	else 
	{
		// またID指定される可能性があるので追加しておく
		AddKeyState(id);
		return false;
	}
}

bool Input::GetKeyStateTrigger(Button::KeyAndMouse id) noexcept
{
	// 配列外にアクセスしないための処理
	if (m_currentKeyState.contains(id))
	{
		return m_currentKeyState[id] && !m_previousKeyState[id];
	}
	else
	{
		// またID指定される可能性があるので追加しておく
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