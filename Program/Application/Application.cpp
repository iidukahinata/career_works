/**
* @file    Application.cpp
* @brief
*
* @date	   2022/05/14 2022年度初版
* @author  飯塚陽太
*/


#include "Application.h"
#include "Game/Game.h"
#include "SubSystem/ThreadPool/ThreadPool.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Tools/COM.h"
#include "SubSystem/Window/Window.h"

bool Application::Init(HINSTANCE hInstance)
{
	// 第３引数 : フルスクリーンモード
	if (!Window::Get().CreateWindowClass(hInstance, 1280, 720, "Test", false))
	{
		return false;
	}

	// 外部からスレッドが使用される可能性があるのでCPU内最大スレッド数の半分を使用
	ThreadPool::Get().Init(ThreadPool::Get().GetMaxThreadCount() / 2);

	m_hInstance = hInstance;

	return true;
}

long Application::MainLoop()
{
	Window& window = Window::Get();
	Timer& timer = Timer::Get();

	Game game;

	game.Init();

	while (window.Tick())
	{
		if (!timer.ReachedNextFrame())
			continue;

		game.Update(timer.GetDeltaTime());
		game.Render(timer.GetDeltaTime());
	}

	game.Exit();

	return window.GetMessage();
}

void Application::Exit()
{
	UnregisterClass("windowClass", m_hInstance);
}