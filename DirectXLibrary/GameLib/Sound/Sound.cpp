/// <filename>
/// Sound.h
/// </filename>
/// <summary>
/// サウンドを管理するクラスのラッパクラスのソース
/// </summary>

#include "Sound.h"

#include <Windows.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <array>

#include <SoundsManager.h>

void Sound::AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey)
{
	size_t tCharLength = _tcsclen(pKey);

	//! 数字と\0の数足す
	size_t additionalKeyLength = tCharLength + 3;

	//! 同じ音声ファイルを10個読み込む
	for (int i = 0; i < SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX; ++i)
	{
		//! ここで文字列操作をして引数のキーの後ろに0~9の数字を付け足したキーを作成している
		m_simultaneousKeys[pKey].m_pKeys[i] = new TCHAR[additionalKeyLength];
		_tcscpy_s(m_simultaneousKeys[pKey].m_pKeys[i], additionalKeyLength, pKey);
		_itot_s(i, &m_simultaneousKeys[pKey].m_pKeys[i][tCharLength], sizeof(TCHAR) * (1 + (i / SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX)), 10);
		m_simultaneousKeys[pKey].m_pKeys[i][tCharLength + 1 + (i / SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX)] = m_TEXT_END;

		//! 上で作ったキーを用いて音声オブジェクトを作成する
		m_soundsManager.AddFile(pFilePath, &m_simultaneousKeys[pKey].m_pKeys[i][0]);
	}
}

void Sound::SimultaneousStartOneShot(const TCHAR* pKey)
{
	//! 最後に流れていたキーの番号
	int currentNum = m_simultaneousKeys[pKey].m_currentPlayNum;

	int prevPrevNum = currentNum - 2;
	if (prevPrevNum < 0)
	{
		prevPrevNum = SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX + prevPrevNum;
	}

	//! 最後に流れていたキーの番号の2つ前の音声を止める,
	//! そうすることにより音声のサイクルをスムーズにし鳴りすぎないようにできる
	Stop(&m_simultaneousKeys[pKey].m_pKeys[prevPrevNum][0]);

	StartOneShot(&m_simultaneousKeys[pKey].m_pKeys[currentNum][0]);

	m_simultaneousKeys[pKey].m_currentPlayNum = (currentNum >= (SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX - 1)) ? 0 : ++currentNum;
}
