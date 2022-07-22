/**
* @file    RenderingThread.cpp
* @brief
*
* @date	   2022/07/22 2022年度初版
*/


#include "RenderingThread.h"
#include "SubSystem/JobSystem/Sync./JobSystem.h"

Queue<RenderCommandList::Command> RenderCommandList::m_commandList;
Queue<RenderCommandList::Command> RenderCommandList::m_taskList;

void RenderCommandList::ReceivingCommand() noexcept
{
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

void RenderingThread::Run()
{
	// 前フレームで追加されたコマンドを実行
	m_renderCommandList.ReceivingCommand();
	m_renderCommandList.CommandProcess();

	JobSystem::Get().Execute(0, FunctionType::Render);
}