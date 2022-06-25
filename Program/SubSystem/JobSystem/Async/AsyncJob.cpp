/**
* @file		AsyncJob.cpp
* @brief
*
* @date		2022/06/16 2022年度初版
*/


#include "AsyncJob.h"
#include "SubSystem/Core/Common/Common.h"

void AsyncJob::Execute() noexcept
{
	// 関数が設定されていない Job が実行されている時、ここで止まります。
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