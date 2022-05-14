/**
* @file    Timer.cpp
* @brief   フレーム管理クラス
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/


#include "Timer.h"

Timer::Timer()
{
	SetFPS(60);
	ResetMeasurement();
}

bool Timer::ReachedNextFrame() noexcept
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms = currentTime - m_previousTime;

	// ミリ秒から秒に変換
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
	if (fps > 0.f)
	{
		m_fpsTime = (1.f / fps);
	}
}

double Timer::GetDeltaTime() const noexcept
{
	return m_deltaTime;
}