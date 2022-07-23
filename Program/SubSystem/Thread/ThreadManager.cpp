/**
* @file    ThreadManager.cpp
* @brief
*
* @date	   2022/07/22 2022”N“x‰”Å
*/


#include "Program/Subsystem/Core/Common/pch.h"
#include "ThreadManager.h"

void ThreadManager::CreateThread(UniquePtr<IThread> thread) noexcept
{
	auto ptr = thread.Release();
	m_threads.emplace_back(ptr);

	m_threadJob.emplace_back([this, ptr]() {
		ptr->Run();
	});
}

void ThreadManager::Tick() noexcept
{
	for (int i = 0; i < m_threadJob.size(); ++i)
	{
		if (!m_threadJob[i].IsTaskFinish())
		{
			continue;
		}

		m_threadJob[i].RegisterToJobSystem();
	}
}