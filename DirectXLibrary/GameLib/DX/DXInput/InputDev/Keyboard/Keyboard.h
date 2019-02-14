/**
* @file Keyboard.h
* @brief キーボードクラスのヘッダ
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>

#include <dinput.h>

#include "../InputDev.h"

/**
* @brief キーボードクラス,基底クラスのInputDevを参照して下さい
*/
class Keyboard :public InputDev
{
public:
	Keyboard(HWND hWnd, LPDIRECTINPUT8 pDXInput) : InputDev(hWnd)
	{
		Create(pDXInput);
	}

	~Keyboard() {};

	/// <summary>
	/// 入力状態の更新,メインループの始まりで用いる
	/// </summary>
	inline VOID UpdataInputState()
	{
		AcquireInputState();
		CheckInputStateDetatils();
	}

	/// <summary>
	/// 入力状態の保存,メインループの終わりで用いる
	/// </summary>
	/// <returns></returns>
	inline VOID StorePrevInputState()
	{
		memcpy(m_prevDiks, m_diks, sizeof(BYTE) * 256);
	}

	/// <summary>
	/// 引数に渡したキーが押された瞬間か
	/// </summary>
	/// <param name="key">キーの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool IsPressed(int key) const
	{
		return (m_details[key] == IND_PRESS);
	}

	inline bool IsHeld(int key) const
	{
		return (m_details[key] == IND_HOLD);
	}

	inline bool IsReleased(int key) const
	{
		return (m_details[key] == IND_RELEASE);
	}

	inline bool IsNeutral(int key) const
	{
		return (m_details[key] == IND_NEUTRAL);
	}

	/// <summary>
	/// 何かのキーが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool AnyKeyIsPressed() const
	{
		const int KEY_MAX = 256;
		for (int i = 0; i < KEY_MAX; ++i)
		{
			if (IsPressed(i)) return true;
		}

		return false;
	}

private:
	VOID Create(LPDIRECTINPUT8 pDXInput);

	inline VOID AcquireInputState()
	{
		//! キーボードの状態を取得する権限の取得
		m_pDInputDev->Acquire();		

		//! キーボードの状態を取得
		m_pDInputDev->GetDeviceState(	
					  sizeof(BYTE) * 256,
					  m_diks);
	}

	/// <summary>
	/// AcquireInputState()を読んだ後に用いる
	/// 入力状態の振り分けを行う
	/// </summary>
	VOID CheckInputStateDetatils();

	//! 現在ののフレームでキーが押されていた場合上位ビットが立つ
	BYTE m_diks[256];					
	
	//! 前回のフレームでキーが押されていた場合上位ビットが立つ
	BYTE m_prevDiks[256];				

	INPUT_DETAIL m_details[256];
};

#endif // !KEYBOARD_H
