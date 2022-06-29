/**
* @file		Job.cpp
* @brief
*
* @date		2022/06/29 2022年度初版
*/


#include "Job.h"
#include "JobSystem.h"
#include "SubSystem/Core/Common/Common.h"

Job::~Job()
{
	// クライアント側で Remove されていなかった場合
	if (m_funcType != FunctionType::None)
	{
		JobSystem::Get().RemoveJob(this);
	}
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