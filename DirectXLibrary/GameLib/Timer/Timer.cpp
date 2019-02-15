﻿/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>

#include "Timer.h"

#include <Windows.h>
#include <chrono>

void Timer::Start()
{
	Reset();
	m_startTime = std::chrono::system_clock::now();
}

void Timer::End()
{
	m_DiffTime = std::chrono::system_clock::now() - m_startTime;
}

void Timer::Reset()
{
	m_isStoped = false;

	m_DiffTime = m_DiffTime.zero();
}

void Timer::Stop()
{
	if (m_isStoped)
	{
		return;
	}

	m_isStoped = true;

	m_startTimeBuff = std::chrono::system_clock::now();
}

void Timer::Restart()
{
	m_isStoped = false;

	m_startTime += (std::chrono::system_clock::now() - m_startTimeBuff);
}

LONGLONG Timer::GetSecond()
{
	End();
	return std::chrono::duration_cast<std::chrono::seconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMilliSecond()
{
	End();
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMicroSecond()
{
	End();
	return std::chrono::duration_cast<std::chrono::microseconds>(m_DiffTime).count();
}