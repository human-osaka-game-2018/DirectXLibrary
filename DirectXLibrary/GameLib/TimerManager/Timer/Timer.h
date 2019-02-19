/// <filename>
/// Timer.h
/// </filename>
/// <summary>
/// 時間計測クラスのヘッダ
/// </summary>

#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <chrono>

/// <summary>
/// 時間計測クラス
/// </summary>
class Timer
{
public:
	Timer() {};
	~Timer() {};

	/// <summary>
	/// 時間の計測開始
	/// </summary>
	void Start();	

	/// <summary>
	/// 時間計測の一時停止
	/// </summary>
	void Pause();	

	/// <summary>
	/// 時間計測のリスタート
	/// </summary>
	void Restart();

	/// <summary>
	/// <para>時間計測の初期化</para>
	/// <para>計測開始時間を現在の開始時間にする</para>
	/// </summary>
	void Reset();

	/// <summary>
	/// 計測時間を返す秒
	/// </summary>
	LONGLONG GetTime_s();

	/// <summary>
	/// 計測時間を返すミリ秒
	/// </summary>
	LONGLONG GetTime_ms();

	/// <summary>
	/// 計測時間を返すマイクロ秒
	/// </summary>
	LONGLONG GetTime_µs();
	
	/// <summary>
	/// 現在計測が止まっているかを返す
	/// </summary>
	/// <returns>止まっていればtrue</returns>
	inline bool IsRunning() const
	{
		return m_isRunning;
	}

private:
	typedef std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> DebugDiffTime;

	/// <summary>
	/// 計測時間を切りとってm_elapsedTimeに代入する
	/// </summary>
	void MeasureElapsedTime();

	std::chrono::system_clock::time_point	m_startTime;	

	std::chrono::system_clock::time_point	m_sysTimeWhenStopped;
	
	DebugDiffTime m_timeWhenStopped;

	DebugDiffTime m_elapsedTime;

	bool m_isRunning = true;
};

#endif //! TIMER_H
