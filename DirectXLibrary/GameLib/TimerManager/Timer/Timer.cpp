/// <filename>
/// Timer.cpp
/// </filename>
/// <summary>
/// 時間計測クラスのソース
/// </summary>

#include "Timer.h"

#include <Windows.h>
#include <chrono>

void Timer::Start()
{
	Reset();
	m_startTime = std::chrono::system_clock::now();
}

void Timer::Pause()
{
	if (!IsRunning()) return;

	m_isRunning = false;

	MeasureElapsedTime();

	m_timeWhenStopped = m_elapsedTime;

	m_sysTimeWhenStopped = std::chrono::system_clock::now();
}

void Timer::Restart()
{
	m_startTime += (std::chrono::system_clock::now() - m_sysTimeWhenStopped);

	m_isRunning = true;
}

void Timer::Reset()
{
	m_elapsedTime = m_elapsedTime.zero();

	m_isRunning = true;
}

LONGLONG Timer::GetTime_s()
{
	if (!IsRunning())
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_timeWhenStopped).count();
	}

	MeasureElapsedTime();
	return std::chrono::duration_cast<std::chrono::seconds>(m_elapsedTime).count();
}

LONGLONG Timer::GetTime_ms()
{
	if (!IsRunning())
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_timeWhenStopped).count();
	}

	MeasureElapsedTime();
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_elapsedTime).count();
}

LONGLONG Timer::GetTime_µs()
{
	if (!IsRunning())
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(m_timeWhenStopped).count();
	}

	MeasureElapsedTime();
	return std::chrono::duration_cast<std::chrono::microseconds>(m_elapsedTime).count();
}

void Timer::MeasureElapsedTime()
{
	m_elapsedTime = std::chrono::system_clock::now() - m_startTime;
}
