/// <filename>
/// TimerManager.h
/// </filename>
/// <summary>
/// 時間関係の管理クラスのヘッダ
/// </summary>

#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <Windows.h>
#include <tchar.h>

#include <chrono>
#include <map>

#include "../Class/Singleton/Singleton.h"

/// <summary>
/// 時間関係の管理クラス
/// </summary>
class TimerManager :public Singleton<TimerManager>
{
public:
	TimerManager()
	{
		Create(_T("fPSTimer"));

		m_timers[_T("fPSTimer")]->Start();
		m_prevFrameSyncTime_ms = m_timers[_T("fPSTimer")]->GetTime_ms();
	}

	~TimerManager()
	{
		ReleaseAll();
	}

	/// <summary>
	/// FPSの設定を行う
	/// </summary>
	/// <param name="fPS">設定したい一秒間でのフレーム数</param>
	/// <remarks>FPSを設定していなかった場合60fps</remarks>
	inline void SetFPS(int fPS)
	{
		m_fPS = fPS;
	}

	/// <summary>
	/// 次のフレームに進んでいいかを判断する
	/// </summary>
	/// <returns>進んでもよければtrue</returns>
	/// <remarks>ここで一フレームにかかった時間を取得する</remarks>
	bool CanStartNextFrame();

	/// <summary>
	/// 一フレームにかかった時間(秒)を取得する
	/// </summary>
	/// <returns>経過時間(秒)</returns>
	float DeltaTime_s() const;

	/// <summary>
	/// タイマーの作成を行う
	/// </summary>
	/// <param name="pKey">生成するタイマーにつける識別キー</param>
	inline void Create(const TCHAR* pKey)
	{
		m_timers[pKey] = new Timer();
	}

	/// <summary>
	/// 引数に渡されたキーのタイマーの開放
	/// </summary>
	/// <param name="pKey">開放したいタイマーのキー</param>
	inline void Release(const TCHAR* pKey)
	{
		if (!Exists(pKey)) return;

		delete m_timers[pKey];
		m_timers.erase(pKey);
	}

	/// <summary>
	/// 引数に渡されたキーのタイマーが存在しているか
	/// </summary>
	/// <param name="pKey">調べたいタイマーの識別キー</param>
	/// <returns>存在していればtrue</returns>
	inline bool Exists(const TCHAR* pKey) const
	{
		return (m_timers.find(pKey) != m_timers.end());
	}

	/// <summary>
	/// 時間の計測開始
	/// </summary>
	/// <param name="pKey">計測開始するタイマーのキー</param>
	inline void Start(const TCHAR* pKey)
	{
		m_timers[pKey]->Start();
	}

	/// <summary>
	/// 時間計測の一時停止
	/// </summary>
	/// <param name="pKey">一時停止するタイマーのキー</param>
	inline void Pause(const TCHAR* pKey)
	{
		m_timers[pKey]->Pause();
	}

	/// <summary>
	/// 時間計測のリスタート
	/// </summary>
	/// <param name="pKey">計測を再スタートさせるタイマーのキー</param>
	inline void Restart(const TCHAR* pKey)
	{
		m_timers[pKey]->Restart();
	}

	/// <summary>
	/// 時間計測の初期化
	/// </summary>
	/// <param name="pKey">初期化したいタイマーのキー</param>
	/// <remarks>計測開始時間を現在の開始時間にする</remarks>
	void Reset(const TCHAR* pKey)
	{
		m_timers[pKey]->Reset();
	}

	/// <summary>
	/// 計測時間を返す(秒)
	/// </summary>
	/// <param name="pKey">タイマーのキー</param>
	inline LONGLONG GetTime_s(const TCHAR* pKey)
	{
		return m_timers[pKey]->GetTime_s();
	}

	/// <summary>
	/// 計測時間を返す(ミリ秒)
	/// </summary>
	/// <param name="pKey">タイマーのキー</param>
	inline LONGLONG GetTime_ms(const TCHAR* pKey)
	{
		return m_timers[pKey]->GetTime_ms();
	}

	/// <summary>
	/// 計測時間を返す(マイクロ秒)
	/// </summary>
	/// <param name="pKey">タイマーのキー</param>
	LONGLONG GetTime_µs(const TCHAR* pKey)
	{
		return m_timers[pKey]->GetTime_µs();
	}

	/// <summary>
	/// 現在計測が止まっているかを返す
	/// </summary>
	/// <param name="pKey">止まっているかを調べるタイマーのキー</param>
	/// <returns>止まっていればtrue</returns>
	inline bool IsRunning(const TCHAR* pKey)
	{
		return m_timers[pKey]->IsRunning();
	}

private:
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
		/// 時間計測の初期化
		/// </summary>
		/// <remarks>計測開始時間を現在の開始時間にする</remarks>
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

	/// <summary>
	/// タイマーの全開放
	/// </summary>
	inline void ReleaseAll()
	{
		for (auto tim : m_timers)
		{
			delete tim.second;
		}
	}

	int m_fPS = 60;

	LONGLONG m_prevFrameSyncTime_ms = NULL;
	LONGLONG m_processTimeAtPrevFrame_ms = NULL;

	std::map<const TCHAR*, Timer*> m_timers;
};

#endif //! TIMER_MANAGER_H
