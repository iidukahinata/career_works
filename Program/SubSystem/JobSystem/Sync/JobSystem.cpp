/**
* @file		JobSystem.cpp
* @brief
*
* @date		2022/06/29 2022�N�x����
*/


#include "JobSystem.h"

void JobSystem::JobContainer::Register(Job* const job) noexcept
{
	m_jobs.insert(job);
}

void JobSystem::JobContainer::Remove(Job* const job) noexcept
{
	m_jobs.erase(job);
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
			job->Execute(deletaTime);
		}
	}
}

void JobSystem::Execute(double deletaTime, FunctionType mode) noexcept
{
	for (auto job : m_containers[mode])
	{
		job->Execute(deletaTime);
	}
}

bool JobSystem::RegisterJob(Job* const job) noexcept
{
	if (job->m_funcType == FunctionType::None)
	{
		LOG_ERROR("FunctionType���w�肵�Ă��������B");
		return false;
	}

	std::unique_lock<std::mutex> lock(m_mutex);

	job->m_funcType = job->m_funcType;
	m_containers[job->m_funcType].Register(job);
	return true;
}

void JobSystem::RemoveJob(Job* const job) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);

	if (job->m_funcType == FunctionType::None)
	{
		return;
	}

	if (m_containers.contains(job->m_funcType))
	{
		m_containers[job->m_funcType].Remove(job);

		// Remove ���� Job �̃f�[�^��\�����ʃo�O��h�����ߏ��������Ă����B
		job->m_funcType = FunctionType::None;
	}
}