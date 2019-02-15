/// <filename>
/// Sound.h
/// </filename>
/// <summary>
/// サウンドを管理するクラスのラッパクラスのヘッダ
/// </summary>

#ifndef SOUND_H
#define SOUND_H

#include <Windows.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <array>

#include <SoundsManager.h>

/// <summary>
/// サウンドを管理するクラスのラッパクラス
/// </summary>
class Sound
{
public:
	Sound()
	{
		m_soundsManager.Initialize();
	}

	~Sound() 
	{
		//! 同時再生用SEの開放
		for (auto i : m_simultaneousKeys)
		{
			for (int si = 0; si < SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX; ++si)
			{
				delete[](i.second.m_pKeys[si]);
			}
		}

		m_simultaneousKeys.clear();
	}

	/// <summary>
	/// 音声ファイルの追加
	/// </summary>
	/// <param name="pFilePath">音声ファイルのパス</param>
	/// <param name="pKey">音声につけるキー</param>
	inline void AddFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_soundsManager.AddFile(pFilePath, pKey);
	}

	/// <summary>
	/// 同時再生用音声ファイルの追加
	/// </summary>
	/// <param name="pFilePath">音声ファイルのパス</param>
	/// <param name="pKey">音声につけるキー</param>
	void AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey);

	/// <summary>
	/// 同時再生用音声の再生(ループなし)
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	void SimultaneousStartOneShot(const TCHAR* pKey);

	/// <summary>
	/// ループ再生させる
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	inline void StartLoop(const TCHAR* pKey)
	{
		m_soundsManager.Start(pKey, true);
	}

	/// <summary>
	/// 音声の再生(ループなし)
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	/// <returns></returns>
	inline void StartOneShot(const TCHAR* pKey)
	{
		m_soundsManager.Start(pKey, false);
	}

	/// <summary>
	/// 音声の一時停止
	/// </summary>
	/// <param name="pKey">一時停止したい音声のキー</param>
	inline void Pause(const TCHAR* pKey)
	{
		m_soundsManager.Pause(pKey);
	}

	/// <summary>
	/// 一時停止していた音声の再生
	/// </summary>
	/// <param name="pKey">再生させたい音声のキー</param>
	inline void Resume(const TCHAR* pKey)
	{
		m_soundsManager.Resume(pKey);
	}

	/// <summary>
	/// 音声の停止
	/// 停止するのには少し時間がかかる
	/// </summary>
	/// <param name="pKey">停止したい音声のキー</param>
	inline void Stop(const TCHAR* pKey)
	{
		m_soundsManager.Stop(pKey);
	}

	/// <summary>
	/// ボリュームの調整
	/// </summary>
	/// <param name="pKey">調整したい音声のキー</param>
	/// <param name="volume">
	/// 0~100までのボリューム
	/// デフォルトでは100
	/// </param>
	inline void SetVolume(const TCHAR* pKey, int volume)
	{
		m_soundsManager.SetVolume(pKey, volume);
	}

private:
	struct SimultaneousKeys
	{
	public:
		static const int m_SIMULTANEOUS_NUM_MAX = 10;
		TCHAR* m_pKeys[m_SIMULTANEOUS_NUM_MAX];
		int m_currentPlayNum = 0;
	};

	SoundLib::SoundsManager m_soundsManager;
	
	const TCHAR m_TEXT_END = _T('\0');

	std::map<const TCHAR*, SimultaneousKeys> m_simultaneousKeys;
};

#endif // !SOUND_H
