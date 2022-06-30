/**
* @file    TickFunction.cpp
* @brief
*
* @date	   2022/06/30 2022îNìxèâî≈
*/


#include "TickFunction.h"
#include "TickManager.h"

void TickFunction::RegisterToTickManager() noexcept
{
	TickManager::Get().AddTickFunction(this);
}

void TickFunction::UnRegisterFromTickManager() noexcept
{
	TickManager::Get().RemoveTickFunction(this);
}

bool TickFunction::IsRegistered() noexcept
{
	return TickManager::Get().HasTickFunction(this);
}

void TickFunction::SetPriority(uint32_t priority) noexcept
{
	if (m_priority == priority)
		return;

	if (IsRegistered())
	{
		UnRegisterFromTickManager();

		m_priority = priority;

		RegisterToTickManager();
	}
	else
	{
		m_priority = priority;
	}
}