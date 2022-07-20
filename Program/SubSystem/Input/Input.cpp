/**
* @file    Input.cpp
* @brief
*
* @date	   2022/07/19 2022îNìxèâî≈
*/


#include "Input.h"
#include "InputEvents.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Core/Event/EventManager.h"

void Input::ShowMouse(bool isShow) const noexcept
{
	ShowCursor(isShow);
}

const Math::Vector2& Input::GetMousePosition() const noexcept
{
	POINT mousePos = {};
	GetCursorPos(&mousePos);
	ScreenToClient(Window::Get().GetHandle(), &mousePos);
	return Math::Vector2(mousePos.x, mousePos.y);
}

void Input::PressKey(Button::KeyAndMouse id) const noexcept
{
	EventManager::Get().AddToQueue(MakeUnique<KeyPressed>(id));
}

void Input::ReleaseKey(Button::KeyAndMouse id) const noexcept
{
	EventManager::Get().AddToQueue(MakeUnique<KeyReleased>(id));
}