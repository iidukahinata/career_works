/**
* @file		Job.cpp
* @brief
*
* @date		2022/06/16 2022�N�x����
*/


#include "Job.h"
#include "JobSystem.h"
#include "SubSystem/Core/Common/Common.h"

Job::~Job()
{
	// �N���C�A���g���� Remove ����Ă��Ȃ������ꍇ
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
	// �֐����ݒ肳��Ă��Ȃ� Job �����s����Ă��鎞�A�����Ŏ~�܂�܂��B
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