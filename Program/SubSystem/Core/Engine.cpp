/**
* @file    Engine.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "Engine.h"
#include "Context.h"
#include "Common/ProjectSettings.h"
#include "Event/EventManager.h"
#include "SubSystem/Audio/Audio.h"
#include "SubSystem/Input/Input.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Scene/World.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"
#include "SubSystem/JobSystem/Async/AsyncJobSystem.h"

bool Engine::Initialize(HINSTANCE hInstance)
{
	bool ret = false;

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
	auto timer = Context::Get()->GetSubsystem<Timer>();

	while (window.Tick())
	{
		if (timer->ReachedNextFrame())
		{
			jobSystem.Execute(timer->GetDeltaTime(), FunctionType::Update);
			jobSystem.Execute(timer->GetDeltaTime(), FunctionType::LateUpdate);

			// renderer thread �Ƃ��ĕ�����\��̂��ߕ������Ă���B
			jobSystem.Execute(timer->GetDeltaTime(), FunctionType::Render);
			jobSystem.Execute(timer->GetDeltaTime(), FunctionType::LateRender);
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

	Context::Get()->Release();
}

bool Engine::StartUpScreen(HINSTANCE hInstance) noexcept
{
	// ��S���� : �t���X�N���[�����[�h�w��
	if (!Window::Get().CreateWindowClass(hInstance, 640, 480, "Test", false))
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
	auto context = Context::Get();
	context->RegisterSubsystem<Timer>(std::make_unique<Timer>());
	context->RegisterSubsystem<Input>(std::make_unique<Input>());
	context->RegisterSubsystem<Audio>(std::make_unique<Audio>());
	context->RegisterSubsystem<ResourceManager>(std::make_unique<ResourceManager>());
	context->RegisterSubsystem<World>(std::make_unique<World>());
	context->RegisterSubsystem<Renderer>(std::make_unique<Renderer>());
}

bool Engine::InitializeSubsystems() noexcept
{
	auto context = Context::Get();

	if (!context->GetSubsystem<Timer>()->Initialize())
	{
		return false;
	}
	
	if (!context->GetSubsystem<Input>()->Initialize())
	{
		return false;
	}
	
	if (!context->GetSubsystem<Audio>()->Initialize())
	{
		return false;
	}

	if (!context->GetSubsystem<ResourceManager>()->Initialize())
	{
		return false;
	}
	 	 
	if (!context->GetSubsystem<Renderer>()->Initialize())
	{
		return false;
	}
	 
	if (!context->GetSubsystem<World>()->Initialize())
	{
		return false;
	}

	return true;
}