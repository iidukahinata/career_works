/**
 * @file	WinAPIInput.cpp
 * @brief   ���͐���N���X
 *
 * @date	2022/07/19 2022�N�x����
 */


#include "WinAPIInput.h"
#include "SubSystem/Window/Window.h"

WinAPIInput::WinAPIInput()
{
	m_job.SetFunction([this](double) { Update(); }, FunctionType::Update);
	m_job.RegisterToJobSystem();
}

bool WinAPIInput::Initialize()
{
	return false;
}

void WinAPIInput::Shutdown()
{
	m_job.UnRegisterFromJobSystem();
}

void WinAPIInput::Update() noexcept
{
	// key���X�V
	//for (auto& key : m_previousKeyState)
	//{
	//	const auto currentState = GetAsyncKeyState(key.first) & 0x8000;
	//
	//	if (currentState && !key.second)
	//	{
	//		PressKey(key.first);
	//	}
	//	else if (!currentState && key.second)
	//	{
	//		ReleaseKey(key.first);
	//	}
	//	key.second = currentState;
	//}
}