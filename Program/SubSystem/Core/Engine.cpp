/**
* @file    Engine.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "Engine.h"
#include "Common/ProjectSettings.h"
#include "Event/EventManager.h"
#include "SubSystem/Audio/FMOD/FMODAudio.h"
#include "SubSystem/Input/Direct/DirectInput.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Scene/World.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/Forward/ForwardRenderer.h"
#include "SubSystem/Renderer/Deferred/DeferredRenderer.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"
#include "SubSystem/JobSystem/Async/AsyncJobSystem.h"
#include "SubSystem/Thread/RenderingThread/RenderingThread.h"

Context* g_context = nullptr;

bool Engine::Initialize(HINSTANCE hInstance)
{
	bool ret = false;

	// system サービスロケータ作成
	m_context = MakeUnique<Context>();
	g_context = m_context.Get();

	ret = StartUpScreen(hInstance);
	if (!ret) {
		LOG_ERROR("StartUpScreenに失敗");
		return false;
	}

	// 外部からスレッドが使用される可能性があるのでCPU内最大スレッド数の半分を使用
	// 最低でも renderer thread と outer thread の2スレッド使用できる用にする。(まだ未完成)
	AsyncJobSystem::Get().Initialize(3);

	EventManager::Get().Initialize();

	RegisterSubsystemsToContainer();

	ret = InitializeSubsystems();
	if (!ret) {
		LOG_ERROR("Subsystemの初期化に失敗");
		return false;
	}

	RenderingThread::Start();

	m_hInstance = hInstance;

	return true;
}

long Engine::MainLoop()
{
	Window& window = Window::Get();
	Timer* timer = m_context->GetSubsystem<Timer>();
	
	while (window.Tick())
	{
		if (timer->ReachedNextFrame())
		{
			RenderingThread::BegineFrame();

			JobSystem::Get().Execute(timer->GetDeltaTime(), FunctionType::Update);

			RenderingThread::EndFrame();
		}
	}

	return window.GetMessage();
}

void Engine::Shutdown()
{
	RenderingThread::Stop();

	EventManager::Get().Exit();

#if DEBUG_MODE_CONSOL
	DebugLog::CloseConsole();
#endif // DEBUG_MODE_CONSOL

	UnregisterClass("windowClass", m_hInstance);

	m_context->Release();
}

bool Engine::StartUpScreen(HINSTANCE hInstance) noexcept
{
	// 第４引数 : フルスクリーンモード指定
	if (!Window::Get().CreateWindowClass(hInstance, 1280, 720, "Test", false))
	{
		return false;
	}

#if DEBUG_MODE_CONSOL
	DebugLog::CreateConsole();
#endif // DEBUG_MODE_CONSOL

	ShowWindow(Window::Get().GetHandle(), SW_SHOW);
	UpdateWindow(Window::Get().GetHandle());
	return true;
}

void Engine::RegisterSubsystemsToContainer() noexcept
{
	m_context->RegisterSubsystem<Timer>(MakeUnique<Timer>());
	m_context->RegisterSubsystem<Input>(MakeUnique<DirectInput>());
	m_context->RegisterSubsystem<Audio>(MakeUnique<FMODAudio>());
	m_context->RegisterSubsystem<ResourceManager>(MakeUnique<ResourceManager>());
	m_context->RegisterSubsystem<World>(MakeUnique<World>());
	m_context->RegisterSubsystem<Renderer>(MakeUnique<ForwardRenderer>());
}

bool Engine::InitializeSubsystems() noexcept
{
	if (!m_context->GetSubsystem<Timer>()->Initialize())
	{
		return false;
	}
	
	if (!m_context->GetSubsystem<Input>()->Initialize())
	{
		return false;
	}
	
	if (!m_context->GetSubsystem<Audio>()->Initialize())
	{
		return false;
	}
	
	if (!m_context->GetSubsystem<ResourceManager>()->Initialize())
	{
		return false;
	}
	 	 
	if (!m_context->GetSubsystem<Renderer>()->Initialize())
	{
		return false;
	}
	 
	if (!m_context->GetSubsystem<World>()->Initialize())
	{
		return false;
	}

	return true;
}