/**
* @file    HitStop.h
* @brief
*
* @date	   2022/06/02 2022îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "HitStop.h"

void HitStop::Start(int fream) noexcept
{
	m_numFream = 0;
	m_endFream = fream;
	m_isHitStop = true;
}

bool HitStop::IsHitStop() noexcept
{
	if (m_isHitStop)
	{
		++m_numFream;
		m_isHitStop = m_numFream <= m_endFream;
	}

	return m_isHitStop;
}