/**
* @file    Input.cpp
* @brief
*
* @date	   2022/06/23 2022年度初版
*/


#include "Input.h"
#include "InputEvents.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Core/Event/EventManager.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"

Input::Input()
{
	m_job.SetFunction([this](double) { Update(); });
	JobSystem::Get().RegisterJob(&m_job, FunctionType::Update);
}

bool Input::Initialize()
{
	AddKey(Button::Rbutton);
	AddKey(Button::Lbutton);
	AddKey(Button::Cancel);
	AddKey(Button::Mbutton);
	AddKey(Button::Xbutton1);
	AddKey(Button::Xbutton2);
	AddKey(Button::Back);
	AddKey(Button::Tab);
	AddKey(Button::Clear);
	AddKey(Button::Return);
	AddKey(Button::Shift);
	AddKey(Button::Control);
	AddKey(Button::Menu);
	AddKey(Button::Pause);
	AddKey(Button::Escape);
	AddKey(Button::SPACE);
	AddKey(Button::Left);
	AddKey(Button::Up);
	AddKey(Button::Right);
	AddKey(Button::Down);
	AddKey(Button::SEelect);
	AddKey(Button::Delete);
	AddKey(Button::Help);
	AddKey(Button::A);
	AddKey(Button::B);
	AddKey(Button::C);
	AddKey(Button::D);
	AddKey(Button::E);
	AddKey(Button::F);
	AddKey(Button::G);
	AddKey(Button::H);
	AddKey(Button::I);
	AddKey(Button::J);
	AddKey(Button::K);
	AddKey(Button::L);
	AddKey(Button::N);
	AddKey(Button::M);
	AddKey(Button::O);
	AddKey(Button::P);
	AddKey(Button::Q);
	AddKey(Button::R);
	AddKey(Button::S);
	AddKey(Button::T);
	AddKey(Button::U);
	AddKey(Button::V);
	AddKey(Button::W);
	AddKey(Button::X);
	AddKey(Button::Y);
	AddKey(Button::Z);
	AddKey(Button::Lwin);
	AddKey(Button::Rwin);
	AddKey(Button::Apps);
	AddKey(Button::Sleep);
	AddKey(Button::F1);
	AddKey(Button::F2);
	AddKey(Button::F3);
	AddKey(Button::F4);
	AddKey(Button::F5);
	AddKey(Button::F6);
	AddKey(Button::F7);
	AddKey(Button::F8);
	AddKey(Button::F9);
	AddKey(Button::F10);
	AddKey(Button::F11);
	AddKey(Button::F12);
	AddKey(Button::Lshift);
	AddKey(Button::Rshift);
	AddKey(Button::Lcontrol);
	AddKey(Button::Rcontrol);
	AddKey(Button::Lmenu);
	AddKey(Button::Rmenu);
	AddKey(Button::Volume_Mute);
	AddKey(Button::Volume_Down);
	AddKey(Button::Volume_Up);

	return true;
}

void Input::Shutdown()
{
	m_previousKeyState.clear();
}

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

void Input::Update() noexcept
{
	// key情報更新
	for (auto& key : m_previousKeyState)
	{
		auto currentState = GetAsyncKeyState(key.first) & 0x8000;

		if (currentState && !key.second)
		{
			PressKey(key.first);
		}
		else if (!currentState && key.second)
		{
			ReleaseKey(key.first);
		}
		key.second = currentState;
	}
}

void Input::AddKey(Button::KeyAndMouse id) noexcept
{
	// 同じIDが重複しないように
	if (!m_previousKeyState.contains(id))
	{
		m_previousKeyState.emplace(id, false);
	}
}

void Input::PressKey(Button::KeyAndMouse id) const noexcept
{
	EventManager::Get().AddToQueue(std::make_shared<KeyPressed>(id));
}

void Input::ReleaseKey(Button::KeyAndMouse id) const noexcept
{
	EventManager::Get().AddToQueue(std::make_shared<KeyReleased>(id));
}