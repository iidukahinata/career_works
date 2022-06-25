/**
* @file		JobSystem.cpp
* @brief
*
* @date		2022/06/16 2022年度初版
*/


#include "JobSystem.h"

void JobSystem::JobContainer::Register(Job* const job) noexcept
{
	m_jobs.push_back(job);

	job->SetPointer(this);
	job->SetId(m_jobs.size() - 1);
}

void JobSystem::JobContainer::Remove(Job* const job) noexcept
{
	// 末端 Job データを指定 Job データ位置に挿入
	m_jobs[job->GetId()] = m_jobs.back();
	m_jobs[job->GetId()]->SetId(job->GetId()); // ID も入れ替える

	m_jobs.pop_back();
	m_jobs.shrink_to_fit();

	// Remove した Job のデータを予期せぬバグを防ぐため初期化しておく。
	job->SetPointer(nullptr);
	job->SetId(-1);
}

auto JobSystem::JobContainer::begin() noexcept
{
	return m_jobs.begin();
}

auto JobSystem::JobContainer::end() noexcept
{
	return m_jobs.end();
}

void JobSystem::Execute(double deletaTime) noexcept
{
	for (auto& container : m_containers)
	{
		for (auto job : container.second)
		{
			if (!job)
			{
				continue;
			}

			job->Execute(deletaTime);
		}
	}
}

void JobSystem::Execute(double deletaTime, FunctionType mode) noexcept
{
	for (auto job : m_containers[mode])
	{
		if (!job)
		{
			continue;
		}

		job->Execute(deletaTime);
	}
}

void JobSystem::RegisterJob(Job* const job, FunctionType mode) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_containers[mode].Register(job);
}

void JobSystem::RemoveJob(Job* const job) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	for (auto& container : m_containers)
	{
		if (&container.second == job->GetPointer())
		{
			container.second.Remove(job);
		}
	}
}