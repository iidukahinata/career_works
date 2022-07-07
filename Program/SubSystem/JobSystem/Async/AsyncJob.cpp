/**
* @file		AsyncJob.cpp
* @brief
*
* @date		2022/07/08 2022�N�x����
*/


#include "AsyncJob.h"
#include "AsyncJobSystem.h"

void AsyncJob::Execute() noexcept
{
	// �֐����ݒ肳��Ă��Ȃ� Job �����s����Ă��鎞�A�����Ŏ~�܂�܂��B
	ASSERT(m_task);

	m_task();
	m_finish = true;
}

void AsyncJob::SetFunction(Task&& task) noexcept
{
	m_task = std::forward<Task>(task);
}

bool AsyncJob::IsTaskFinish() const noexcept
{
	return m_finish;
}

void AsyncJob::RegisterToJobSystem()
{
	AsyncJobSystem::Get().AddTask(this);
}