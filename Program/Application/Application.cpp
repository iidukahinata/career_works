/**
* @file    Application.cpp
* @brief
*
* @date	   2022/05/14 2022�N�x����
* @author  �ђ˗z��
*/


#include "Application.h"
#include "Game/Game.h"
#include "SubSystem/ThreadPool/ThreadPool.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Tools/COM.h"
#include "SubSystem/Window/Window.h"

bool Application::Init(HINSTANCE hInstance)
{
	// ��R���� : �t���X�N���[�����[�h
	if (!Window::Get().CreateWindowClass(hInstance, 1280, 720, "Test", false))
	{
		return false;
	}

	// �O������X���b�h���g�p�����\��������̂�CPU���ő�X���b�h���̔������g�p
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