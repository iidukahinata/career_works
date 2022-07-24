/**
* @file    ThreadManager.cpp
* @brief
*
* @date	   2022/07/24 2022�N�x����
*/


#include "ThreadManager.h"

void ThreadManager::QuitThread(StringView threadName) noexcept
{
	const uint32_t threadId = GetHashFromCRC(threadName);

	if (!m_threads.contains(threadId))
	{
		return;
	}

	m_threads[threadId]->RequestQuit();

	// thread loop ���I������܂őҋ@
	while (!m_threadJob[threadId].IsTaskFinish())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(8));
	}

	// �������
	UnRegisterThread(threadId);
	RemoveAsyncJob(threadId);
}

void ThreadManager::RegisterThread(IThread* ptr, const uint32_t hash) noexcept
{
	ASSERT(!m_threads.contains(hash));
	m_threads[hash].Reset(ptr);
}

void ThreadManager::UnRegisterThread(const uint32_t hash) noexcept
{
	if (m_threads.contains(hash))
	{
		m_threads.erase(hash);
	}
}

void ThreadManager::RemoveAsyncJob(const uint32_t hash) noexcept
{
	if (m_threadJob.contains(hash))
	{
		m_threadJob.erase(hash);
	}
}