/**
* @file		Job.cpp
* @brief
*
* @date		2022/06/29 2022年度初版
*/


#include "Job.h"
#include "JobSystem.h"

Job::~Job()
{
	// クライアント側で Remove されていなかった場合
	UnRegisterFromJobSystem();
}

Job::Job(Task&& task, FunctionType type) noexcept
{
	SetFunction(std::forward<Task>(task), type);
}

void Job::Execute(double deletaTime) noexcept
{
	// 関数が設定されていない Job が実行されている時、ここで止まります。
	ASSERT(m_task);
	m_task(deletaTime);
}

void Job::SetFunction(Task&& task, FunctionType fincType) noexcept
{
	m_funcType = fincType;
	m_task = std::forward<Task>(task);
}

void Job::RegisterToJobSystem() noexcept
{
	if (!IsRegistered())
	{
		m_isRegistered = true;
		JobSystem::Get().RegisterJob(this);
	}
}

void Job::UnRegisterFromJobSystem() noexcept
{
	if (IsRegistered())
	{
		m_isRegistered = false;
		JobSystem::Get().RemoveJob(this);
	}
}

bool Job::IsRegistered() const noexcept
{
	return m_isRegistered;
}