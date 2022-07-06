/**
* @file    TickManager.cpp
* @brief
*
* @date	   2022/07/06 2022”N“x‰”Å
*/


#include "TickManager.h"

void TickManager::Tick(double deltaTime) noexcept
{
	for (const auto container : m_tickContainers)
	{
		for (const auto function : container.second)
		{
			function->Tick(deltaTime);
		}
	}
}

void TickManager::RegisterTickFunction(TickFunction* function) noexcept
{
	ASSERT(!m_allTickFunctions.contains(function));

	AddTickFunction(function);
	m_allTickFunctions.insert(function);
}

void TickManager::UnRegisterTickFunction(TickFunction* function) noexcept
{
	RemoveTickFunction(function);
	m_allTickFunctions.erase(function);
}

void TickManager::AddTickFunction(TickFunction* function) noexcept
{
	ASSERT(function->IsRegistered());

	if (function->GetEnable())
	{
		const auto id = function->GetPriority();
		m_tickContainers[id].insert(function);
	}
}

void TickManager::RemoveTickFunction(TickFunction* function) noexcept
{
	ASSERT(function->IsRegistered());

	if (function->GetEnable())
	{
		const auto id = function->GetPriority();
		if (m_tickContainers.contains(id))
		{
			m_tickContainers[id].erase(function);
		}
	}
}

bool TickManager::HasTickFunction(TickFunction* function) noexcept
{
	return m_allTickFunctions.contains(function);
}