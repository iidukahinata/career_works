/**
* @file    ThreadManager.h
* @brief
*
* @date	   2022/07/22 2022”N“x‰”Å
*/
#pragma once


#include "Thread.h"

class ThreadManager
{
public:

	static ThreadManager& Get() noexcept
	{
		static ThreadManager instance;
		return instance;
	}

	void CreateThread(UniquePtr<IThread> thread) noexcept;

	void Tick() noexcept;

private:

	Vector<UniquePtr<IThread>> m_threads;
	Vector<AsyncJob> m_threadJob;
};