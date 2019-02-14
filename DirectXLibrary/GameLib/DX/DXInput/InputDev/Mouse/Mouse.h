/**
* @file Mouse.h
* @brief マウスクラスのヘッダ
*/

#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>

#include <dinput.h>

#include "../InputDev.h"
#include "Enum/DIM.h"

/**
* @brief マウスクラス,基底クラスのInputDevを参照して下さい
*/
class Mouse :public InputDev
{
public:
	Mouse(HWND hWnd, LPDIRECTINPUT8 pDXInput) : InputDev(hWnd)
	{
		Create(pDXInput);
	}

	~Mouse() {};

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
		memcpy(&m_prevState, &m_state, sizeof(DIMOUSESTATE));
	}

	/// <summary>
	/// 引数に渡したボタンが押された瞬間か
	/// </summary>
	/// <param name="key">ボタンの列挙体</param>
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
	/// 何かのボタンが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool AnyKeyIsPressed() const
	{
		for (int i = 0; i < DIM_MAX; ++i)
		{
			if (IsPressed(i)) return true;
		}

		return false;
	}

	/// <summary>
	/// カーソルの位置の取得
	/// </summary>
	/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
	inline VOID CursorPos(POINT* pPos) const
	{
		*pPos = m_cursorRelativePos;
	}

	/// <summary>
	/// 前フレームからどのくらいスクロールされたか
	/// </summary>
	/// <returns>スクロールされた量</returns>
	inline long WheelScrollingFromPrev() const
	{
		return m_state.lZ;
	}

private:
	VOID Create(LPDIRECTINPUT8 pDXInput);

	VOID AcquireInputState();

	/// <summary>
	/// AcquireInputState()を読んだ後に用いる
	/// 入力状態の振り分けを行う
	/// </summary>
	VOID CheckInputStateDetatils();

	DIMOUSESTATE m_state;
	DIMOUSESTATE m_prevState;

	//! カーソルのウィンドウ基準の相対座標
	POINT m_cursorRelativePos;							

	INPUT_DETAIL m_details[DIM_MAX];
};

#endif // !MOUSE_H
