/**
* @file    SpinLock.h
* @brief
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once

#include <atomic>

/**
* std::mutex ���g�p���Ȃ��r��������s��
*/
class SpinLock 
{
public:

	void Lock();
	void Unlock();

private:

	std::atomic_flag m_isRewriting = ATOMIC_FLAG_INIT;
};