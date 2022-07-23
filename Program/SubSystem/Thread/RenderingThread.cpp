/**
* @file    RenderingThread.cpp
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/


#include "RenderingThread.h"
#include "SubSystem/JobSystem/Sync./JobSystem.h"
#include "RenderingThread/RenderCommandFance.h"

void FlushRenderCommand() noexcept
{
	RenderCommandFance renderCommandFance;
	renderCommandFance.BegineFrame();
	renderCommandFance.WaitForSingle();
}

std::mutex RenderCommandList::m_mutex;
Queue<RenderCommandList::Command> RenderCommandList::m_commandList;
Queue<RenderCommandList::Command> RenderCommandList::m_taskList;

void RenderCommandList::ReceivingCommand() noexcept
{
	std::unique_lock lock(m_mutex);
	m_commandList.swap(m_taskList);
}

void RenderCommandList::CommandProcess() noexcept
{
	while (!m_commandList.empty())
	{
		auto&& command = std::move(m_commandList.front());

		// command �̎��s
		command();

		m_commandList.pop();
	}
}

void RenderingThread::Run()
{
	// �O�t���[���Œǉ����ꂽ�R�}���h�����s
	m_renderCommandList.ReceivingCommand();
	m_renderCommandList.CommandProcess();

	JobSystem::Get().Execute(0, FunctionType::Render);
}