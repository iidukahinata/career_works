/**
* @file    Timer.cpp
* @brief   �t���[���Ǘ��N���X
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "Timer.h"
#include "SubSystem/Tools/Chack.h"

Timer::Timer()
{
	SetFPS(60);
	ResetMeasurement();
}

bool Timer::ReachedNextFrame() noexcept
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms = currentTime - m_previousTime;

	// �~���b����b�ɕϊ�
	m_deltaTime = ms.count() / 1000.0;
	if (m_deltaTime >= m_fpsTime)
	{
		m_previousTime = std::move(currentTime);
		return true;
	}
	return false;
}

void Timer::ResetMeasurement() noexcept
{
	m_deltaTime = 0.f;
	m_previousTime = std::chrono::high_resolution_clock::now();
}

void Timer::SetFPS(float fps) noexcept
{
	Chack(fps > 0.f);
	m_fpsTime = (1.f / fps);
}

double Timer::GetDeltaTime() const noexcept
{
	return m_deltaTime;
}