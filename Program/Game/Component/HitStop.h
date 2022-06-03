/**
* @file    HitStop.h
* @brief
*
* @date	   2022/06/02 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


class HitStop
{
public:

	void Start(int fream) noexcept;

	bool IsHitStop() noexcept;

private:

	int m_numFream = 0;
	int m_endFream = 0;
	bool m_isHitStop = false;
};