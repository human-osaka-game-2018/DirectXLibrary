/**
* @file InputDev.h
* @brief 入力デバイスの基底クラスのヘッダ
*/

#ifndef INPUT_DEV_H
#define INPUT_DEV_H

#include <Windows.h>

#include <dinput.h>

/**
* @brief 入力デバイスの基底クラス
*/
class InputDev
{
public:
	InputDev(HWND hWnd) :m_HWND(hWnd) {};

	virtual ~InputDev()
	{
		m_pDInputDev->Release();
	}

	/**
	* @brief 入力デバイスの状態の取得,その後詳細な振り分けを行う,メッセージループの始まりで呼ぶ
	*/
	virtual void UpdataInputState() = 0;

	/**
	* @brief 入力状態の詳細な振り分けを行うため入力状態の保存を行う,メッセージループの終わりで呼ぶ
	*/
	virtual void StorePrevInputState() = 0;

	/**
	* @brief 引数のキーが押された瞬間かを返す
	* @param key 判別したいキーの番号,マウスの場合DIM列挙体,キーボードの場合DIK定数
	* @return 押された瞬間の場合true,そうでなければfalse
	*/
	virtual bool IsPressed(int key) const = 0;

	/**
	* @brief 引数のキーが押されているかを返す
	* @param key 判別したいキーの番号,マウスの場合DIM列挙体,キーボードの場合DIK定数
	* @return 押されている場合true,そうでなければfalse
	*/
	virtual bool IsHeld(int key) const = 0;

	/**
	* @brief 引数のキーがはなされた瞬間かを返す
	* @param key 判別したいキーの番号,マウスの場合DIM列挙体,キーボードの場合DIK定数
	* @return はなされた瞬間の場合true,そうでなければfalse
	*/
	virtual bool IsReleased(int key) const = 0;

	/**
	* @brief 引数のキーがはなされているかを返す
	* @param key 判別したいキーの番号,マウスの場合DIM列挙体,キーボードの場合DIK定数
	* @return はなされている場合true,そうでなければfalse
	*/
	virtual bool IsNeutral(int key) const = 0;

	/**
	* @brief 何か入力されたを返す
	* @return 入力されていたらtrue
	*/
	virtual bool AnyKeyIsPressed() const = 0;

protected:
	enum INPUT_DETAIL
	{
		//! 押された瞬間のフレームだけtrue
		IND_PRESS,										
		
		//! 押され続けられている間true
		IND_HOLD,										
		
		//! 離された瞬間のフレームだけtrue
		IND_RELEASE,									
		
		//! 前回と現在のフレームで押されていない間true
		IND_NEUTRAL,									
		IND_MAX
	};

	virtual void AcquireInputState() = 0;
	virtual void CheckInputStateDetatils() = 0;

	inline bool IsInputted(const BYTE& rKey) const
	{
		return (rKey & 0x80);
	}

	const HWND m_HWND = nullptr;

	LPDIRECTINPUTDEVICE8 m_pDInputDev = nullptr;
};

#endif // !INPUT_DEV_H
