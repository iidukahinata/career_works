/**
* @file    RenderingThread.cpp
* @brief
*
* @date	   2022/07/24 2022年度初版
*/


#include "RenderingThread.h"
#include "RenderCommandFance.h"
#include "SubSystem/JobSystem/Sync./JobSystem.h"
#include "SubSystem/Thread/ThreadManager.h"
#include "SubSystem/Editer/EditerSystem.h"

std::mutex RenderCommandList::m_mutex;
Queue<RenderCommandList::Command> RenderCommandList::m_commandList;
Queue<RenderCommandList::Command> RenderCommandList::m_taskList;

void RenderCommandList::ReceivingCommand() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_commandList.swap(m_taskList);
}

void RenderCommandList::CommandProcess() noexcept
{
	while (!m_commandList.empty())
	{
		auto&& command = std::move(m_commandList.front());

		// command の実行
		command();

		m_commandList.pop();
	}
}

void RenderingThread::Start() noexcept
{
	// register and run thread
	ThreadManager::Get().CreateThread<RenderingThread>();

	EditerSystem::Get().Initialize();

	// renderingThread が正常動作しているか確認。
	WiatForRenderCommand();
}

void RenderingThread::Stop() noexcept
{
	WiatForRenderCommand();

	// unregister
	ThreadManager::Get().QuitThread(RenderingThread::TypeData.Name);

	EditerSystem::Get().Exit();
}

void RenderingThread::BegineFrame() noexcept
{
	RegisterRenderCommand([] {

		// この実装方法では処理がGameThreadが早すぎる場合、操作関数コマンドを実行しないなどの問題がある
		RenderCommandList::FlushCommand();

		EditerSystem::Get().BegineFrame();
	});
}

void RenderingThread::EndFrame() noexcept
{
	RegisterRenderCommand([] {
		JobSystem::Get().Execute(0, FunctionType::Render);
	});
}

void RenderingThread::WiatForRenderCommand() noexcept
{
	RenderCommandFance renderCommandFance;
	renderCommandFance.BegineFrame();
	renderCommandFance.WaitForSingle();
}

void RenderingThread::Run()
{
	while (!IsRequestQuit())
	{
		// 前フレームで追加されたコマンドを実行
		m_renderCommandList.ReceivingCommand();
		m_renderCommandList.CommandProcess();
	}
}