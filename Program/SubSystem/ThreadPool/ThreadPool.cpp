/**
* @file    ThreadPool.cpp
* @brief	並列処理クラス
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
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

	// threadに対して終了を報告
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isRunning = false;
	lock.unlock();

	m_conditionVar.notify_all();

	// 実行中の処理が終了するまで待機
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

	// 最後のタスクが実行されるまで待機
	while (!m_tasks.empty())
	{}

	while (m_isRunning)
	{
		// 全ての thread が使用可能になるまで待機
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
	// 読み込み処理等で使用されるため各スレッドで COM オブジェクト生成。
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