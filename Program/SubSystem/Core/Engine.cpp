/**
* @file    Engine.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "Engine.h"
#include "Common/ProjectSettings.h"
#include "Event/EventManager.h"
#include "SubSystem/Audio/FMOD/FMODAudio.h"
#include "SubSystem/Input/Input.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Scene/World.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"
#include "SubSystem/JobSystem/Async/AsyncJobSystem.h"

Context* g_context = nullptr;

bool Engine::Initialize(HINSTANCE hInstance)
{
	bool ret = false;

	m_context = MakeUnique<Context>();
	g_context = m_context.Get();

	ret = StartUpScreen(hInstance);
	if (!ret) {
		LOG_ERROR("StartUpScreen�Ɏ��s");
		return false;
	}

	// �O������X���b�h���g�p�����\��������̂�CPU���ő�X���b�h���̔������g�p
	// �Œ�ł� renderer thread �� outer thread ��2�X���b�h�g�p�ł���p�ɂ���B(�܂�������)
	//AsyncJobSystem::Get().Initialize(AsyncJobSystem::Get().GetMaxThreadCount() / 2);

	EventManager::Get().Initialize();

	RegisterSubsystemsToContainer();

	ret = InitializeSubsystems();
	if (!ret) {
		LOG_ERROR("Subsystem�̏������Ɏ��s");
		return false;
	}

	m_hInstance = hInstance;

	return true;
}

long Engine::MainLoop()
{
	Window& window = Window::Get();
	auto& jobSystem = JobSystem::Get();
	auto timer = m_context->GetSubsystem<Timer>();
	
	while (window.Tick())
	{
		if (timer->ReachedNextFrame())
		{
			jobSystem.Execute(timer->GetDeltaTime(), FunctionType::Update);
	
			// renderer thread �Ƃ��ĕ�����\��̂��ߕ������Ă���B
			jobSystem.Execute(timer->GetDeltaTime(), FunctionType::Render);
		}
	}

	return window.GetMessage();
}

void Engine::Shutdown()
{
	EventManager::Get().Exit();

#if DEBUG_MODE_CONSOL
	DebugLog::CloseConsole();
#endif // DEBUG_MODE_CONSOL

	UnregisterClass("windowClass", m_hInstance);

	m_context->Release();
}

bool Engine::StartUpScreen(HINSTANCE hInstance) noexcept
{
	// ��S���� : �t���X�N���[�����[�h�w��
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
	m_context->RegisterSubsystem<Input>(MakeUnique<Input>());
	m_context->RegisterSubsystem<Audio>(MakeUnique<FMODAudio>());
	m_context->RegisterSubsystem<ResourceManager>(MakeUnique<ResourceManager>());
	m_context->RegisterSubsystem<World>(MakeUnique<World>());
	m_context->RegisterSubsystem<Renderer>(MakeUnique<Renderer>());
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