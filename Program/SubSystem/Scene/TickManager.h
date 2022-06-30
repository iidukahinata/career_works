/**
* @file    TickManager.h
* @brief
*
* @date	   2022/06/30 2022îNìxèâî≈
*/
#pragma once


#include <map>
#include <set>
#include "TickFunction.h"

class TickManager
{
	typedef std::set<TickFunction*> TickContainer;
public:

	static TickManager& Get()
	{
		static TickManager instance;
		return instance;
	}

	void Tick(double deltaTime) noexcept;

	void AddTickFunction(TickFunction* function) noexcept;
	void RemoveTickFunction(TickFunction* function) noexcept;

	bool HasTickFunction(TickFunction* function) noexcept;

private:

	std::map<uint32_t, TickContainer> m_tickContainers;
};