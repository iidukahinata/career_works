/**
* @file    SpinLock.cpp
* @brief
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/


#include "SpinLock.h"

void SpinLock::Lock() 
{
	while (m_isRewriting.test_and_set(std::memory_order_acquire))
	{
		while (m_isRewriting.test(std::memory_order_relaxed)) {
			// sleep_for での待ちでの実装でも可能。

			// 待機しているスレッドにリソースを渡す。
			// しかし、一部のプラットフォームでは無効になる。
			_YIELD_PROCESSOR();
		}
	}
}

void SpinLock::Unlock() 
{
	m_isRewriting.clear(std::memory_order_release);
}