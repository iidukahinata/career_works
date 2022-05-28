/**
* @file    ThreadPool.cpp
* @brief	���񏈗��N���X
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "ThreadPool.h"
#include "SubSystem/Tools/Chack.h"
#include "SubSystem/Tools/COM.h"

ThreadPool::~ThreadPool()
{
	Stop();
}

bool ThreadPool::Init(int threadCount) noexcept
{
	Chack(threadCount > 0);
	Chack(threadCount <= GetMaxThreadCount());

	if (m_isRunning)
		return true;

	m_isRunning = true;

	for (int i = 0; i < threadCount; ++i)
	{
		m_threads.emplace_back(&ThreadPool::ThreadLoop, this);
	}
	return true;
}

void ThreadPool::Stop() noexcept
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
}

bool ThreadPool::WaitForAllTasksToFinish() const noexcept
{
	if (!m_isRunning)
		return false;

	// �Ō�̃^�X�N�����s�����܂őҋ@
	while (!m_tasks.empty())
	{}

	while (m_isRunning)
	{
		// �S�Ă� thread ���g�p�\�ɂȂ�܂őҋ@
		if (m_numOfThreadsAvailable == m_threads.size())
			break;
	}
	return true;
}

int ThreadPool::GetMaxThreadCount() const noexcept
{
	return std::thread::hardware_concurrency();
}

void ThreadPool::AddTask(ThreadClosure&& function) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_tasks.emplace(std::bind(std::forward<ThreadClosure>(function)));

	lock.unlock();

	m_conditionVar.notify_one();
}

inline void ThreadPool::ThreadLoop() noexcept
{
	// �ǂݍ��ݏ������Ŏg�p����邽�ߊe�X���b�h�� COM �I�u�W�F�N�g�����B
	COM com(COMID::MULTITHREADED);

	while (true)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		++m_numOfThreadsAvailable;

		m_conditionVar.wait(lock, [this] { return !m_tasks.empty() || !m_isRunning; });
		if (m_tasks.empty() && !m_isRunning)
			return;

		--m_numOfThreadsAvailable;

		auto task = std::move(m_tasks.front());
		m_tasks.pop();
		lock.unlock();

		task();
	}
}