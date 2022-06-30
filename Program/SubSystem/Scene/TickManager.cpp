/**
* @file    TickManager.cpp
* @brief
*
* @date	   2022/06/30 2022”N“x‰”Å
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

void TickManager::AddTickFunction(TickFunction* function) noexcept
{
	const auto id = function->GetPriority();
	m_tickContainers[id].insert(function);
}

void TickManager::RemoveTickFunction(TickFunction* function) noexcept
{
	const auto id = function->GetPriority();
	if (m_tickContainers.contains(id))
	{
		m_tickContainers[id].erase(function);
	}
}

bool TickManager::HasTickFunction(TickFunction* function) noexcept
{
	const auto id = function->GetPriority();
	return m_tickContainers.contains(id) && m_tickContainers[id].contains(function);
}