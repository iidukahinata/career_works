/**
 * @file	WinAPIInput.cpp
 * @brief   入力制御クラス
 *
 * @date	2022/07/19 2022年度初版
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
	// key情報更新
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