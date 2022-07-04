/**
* @file    AsyncJobSystem.cpp
* @brief
*
* @date	   2022/07/05 2022�N�x����
*/


#include "AsyncJobSystem.h"
#include "COM.h"

AsyncJobSystem::~AsyncJobSystem()
{
	Stop();
}

bool AsyncJobSystem::Initialize(int threadCount) noexcept
{
	ASSERT(threadCount > 0);
	ASSERT(threadCount <= GetMaxThreadCount());

	if (m_isRunning)
		return true;

	m_isRunning = true;

	for (int i = 0; i < threadCount; ++i)
	{
		m_threads.emplace_back(&AsyncJobSystem::ThreadLoop, this);
	}
	return true;
}

void AsyncJobSystem::Stop() noexcept
{
	if (!m_isRunning)
		return;

	// thread�ɑ΂��ďI�����
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isRunning = false;
	lock.unlock();

	m_conditionVar.notify_all();

	// ���s���̏������I������܂őҋ@
	for (auto& thread : m_threads)
	{
		thread.join();
	}

	m_threads.clear();
	m_threads.shrink_to_fit();
}

int AsyncJobSystem::GetMaxThreadCount() const noexcept
{
	return std::thread::hardware_concurrency();
}

void AsyncJobSystem::AddTask(AsyncJob* job) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_tasks.emplace(job);

	m_conditionVar.notify_one();
}

inline void AsyncJobSystem::ThreadLoop() noexcept
{
	// �ǂݍ��ݏ������Ŏg�p����邽�ߊe�X���b�h�� COM �I�u�W�F�N�g�����B
	COM com(COMID::MULTITHREADED);

	while (true)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		m_conditionVar.wait(lock, [this] { return !m_tasks.empty() || !m_isRunning; });
		if (m_tasks.empty() && !m_isRunning)
			return;

		auto task = std::move(m_tasks.front());
		m_tasks.pop();
		lock.unlock();

		task->Execute();
	}
}