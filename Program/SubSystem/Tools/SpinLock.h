/**
* @file    SpinLock.h
* @brief
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/
#pragma once

#include <atomic>

/**
* std::mutex を使用しない排他制御を行う
*/
class SpinLock 
{
public:

	void Lock();
	void Unlock();

private:

	std::atomic_flag m_isRewriting = ATOMIC_FLAG_INIT;
};