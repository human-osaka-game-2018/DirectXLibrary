/// <filename>
/// TimerManager.cpp
/// </filename>
/// <summary>
/// 時間関係の管理クラスのソース
/// </summary>

#include "TimerManager.h"

#include <Windows.h>
#include <tchar.h>

#include <chrono>
#include <map>

void TimerManager::Timer::Start()
{
	Reset();
	m_startTime = std::chrono::system_clock::now();
}

void TimerManager::Timer::Pause()
{
	if (!IsRunning()) return;

	m_isRunning = false;

	MeasureElapsedTime();

	m_timeWhenStopped = m_elapsedTime;

	m_sysTimeWhenStopped = std::chrono::system_clock::now();
}

void TimerManager::Timer::Restart()
{
	m_startTime += (std::chrono::system_clock::now() - m_sysTimeWhenStopped);

	m_isRunning = true;
}

void TimerManager::Timer::Reset()
{
	m_elapsedTime = m_elapsedTime.zero();

	m_isRunning = true;
}

LONGLONG TimerManager::Timer::GetTime_s()
{
	if (!IsRunning())
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_timeWhenStopped).count();
	}

	MeasureElapsedTime();
	return std::chrono::duration_cast<std::chrono::seconds>(m_elapsedTime).count();
}

LONGLONG TimerManager::Timer::GetTime_ms()
{
	if (!IsRunning())
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_timeWhenStopped).count();
	}

	MeasureElapsedTime();
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_elapsedTime).count();
}

LONGLONG TimerManager::Timer::GetTime_µs()
{
	if (!IsRunning())
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(m_timeWhenStopped).count();
	}

	MeasureElapsedTime();
	return std::chrono::duration_cast<std::chrono::microseconds>(m_elapsedTime).count();
}

void TimerManager::Timer::MeasureElapsedTime()
{
	m_elapsedTime = std::chrono::system_clock::now() - m_startTime;
}

bool TimerManager::CanStartNextFrame()
{
	LONGLONG currenFrameSynctTime_ms = m_timers[_T("fPSTimer")]->GetTime_ms();

	if (currenFrameSynctTime_ms - m_prevFrameSyncTime_ms < 1000 / m_fPS) return false;

	// 一フレームにかかった時間をDeltaTime_sのため取得する
	m_processTimeAtPrevFrame_ms = m_prevFrameSyncTime_ms - currenFrameSynctTime_ms;

	m_prevFrameSyncTime_ms = currenFrameSynctTime_ms;

	return true;
}

float TimerManager::DeltaTime_s() const
{
	float deltaTime_s = static_cast<float>(m_processTimeAtPrevFrame_ms) / 1000.0f;

	return deltaTime_s;
}
