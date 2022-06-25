/**
* @file		Job.cpp
* @brief
*
* @date		2022/06/16 2022年度初版
*/


#include "Job.h"
#include "JobSystem.h"
#include "SubSystem/Core/Common/Common.h"

Job::~Job()
{
	// クライアント側で Remove されていなかった場合
	if (m_jobContainer)
	{
		JobSystem::Get().RemoveJob(this);
	}
}

Job::Job(Task&& task) noexcept
{
	SetFunction(std::forward<Task>(task));
}

void Job::Execute(double deletaTime) noexcept
{
	// 関数が設定されていない Job が実行されている時、ここで止まります。
	ASSERT(m_task);
	m_task(deletaTime);
}

void Job::SetFunction(Task&& task) noexcept
{
	m_task = std::forward<Task>(task);
}

void Job::SetPointer(Job::Pointer jobContainer) noexcept
{
	m_jobContainer = jobContainer;
}

Job::Pointer Job::GetPointer() const noexcept
{
	return m_jobContainer;
}

void Job::SetId(uint32_t id) noexcept
{
	m_id = id;
}

uint32_t Job::GetId() const noexcept
{
	return m_id;
}