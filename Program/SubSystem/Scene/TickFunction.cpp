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
	if (!IsRegistered())
	{
		m_isRegistered = true;
		TickManager::Get().RegisterTickFunction(this);
	}
}

void TickFunction::UnRegisterFromTickManager() noexcept
{
	if (IsRegistered())
	{
		m_isRegistered = false;
		TickManager::Get().UnRegisterTickFunction(this);
	}
}

bool TickFunction::IsRegistered() const noexcept
{
	return m_isRegistered;
}

void TickFunction::SetEnable(bool enable) noexcept
{
	if (m_isEnabled == enable)
		return;

	if (IsRegistered())
	{
		TickManager::Get().RemoveTickFunction(this);
		m_isEnabled = enable;
		TickManager::Get().AddTickFunction(this);
	}
	else
	{
		m_isEnabled = enable;
	}
}

bool TickFunction::GetEnable() noexcept
{
	return m_isEnabled;
}

void TickFunction::SetPriority(uint32_t priority) noexcept
{
	if (m_priority == priority)
		return;

	if (IsRegistered())
	{
		TickManager::Get().RemoveTickFunction(this);
		m_priority = priority;
		TickManager::Get().AddTickFunction(this);
	}
	else
	{
		m_priority = priority;
	}
}

uint32_t TickFunction::GetPriority() const noexcept
{
	return m_priority;
}