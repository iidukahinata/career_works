/**
* @file    SpinLock.cpp
* @brief
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
*/


#include "SpinLock.h"

void SpinLock::Lock() 
{
	while (m_isRewriting.test_and_set(std::memory_order_acquire))
	{
		while (m_isRewriting.test(std::memory_order_relaxed)) {
			// sleep_for �ł̑҂��ł̎����ł��\�B

			// �ҋ@���Ă���X���b�h�Ƀ��\�[�X��n���B
			// �������A�ꕔ�̃v���b�g�t�H�[���ł͖����ɂȂ�B
			_YIELD_PROCESSOR();
		}
	}
}

void SpinLock::Unlock() 
{
	m_isRewriting.clear(std::memory_order_release);
}