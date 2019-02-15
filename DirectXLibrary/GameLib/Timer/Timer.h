/**
 *@file Timer.h
 *@brief 時間を計るクラスのヘッダ
 */

#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <chrono>

/**
 *@brief 
 */
class Timer
{
public:
	Timer() {};
	~Timer() {};

	void Start();					
	void End();						
	void Reset();					
	void Stop();					
	void Restart();					//! 経過時間分スタート時間をたしていく
	LONGLONG GetSecond();			//! 秒を取得
	LONGLONG GetMilliSecond();		//! ミリ秒取得
	LONGLONG GetMicroSecond();		//! マイクロ秒取得

	inline bool GetIsStoped()
	{
		return m_isStoped;
	}

private:
	typedef std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> DebugDiffTime;

	//!< 計測開始時間.
	std::chrono::system_clock::time_point	m_startTime;	

	std::chrono::system_clock::time_point	m_startTimeBuff;
	
	//!< 計測時間.
	DebugDiffTime m_DiffTime;

	bool m_isStoped = false;
};

#endif // !TIMER_H_
