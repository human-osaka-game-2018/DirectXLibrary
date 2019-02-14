/**
* @file DXInput.h
* @brief 入力デバイス関係クラスのFacadeのヘッダ
* @author Harutaka-Tsujino
*/

#ifndef DX_INPUT_H
#define DX_INPUT_H

#include <Windows.h>

#include <d3dx9.h>
#include <dinput.h>

#include "InputDev/InputDev.h"
#include "InputDev/Mouse/Mouse.h"
#include "InputDev/Keyboard/Keyboard.h"

/**
* @brief 入力デバイス関係クラスのFacade
*/
class DXInput
{
public:
	DXInput(HWND hWnd) :m_HWND(hWnd)
	{
		Create();

		m_pMouse	= new Mouse(m_HWND, m_pDXInput);
		m_pKeyboard = new Keyboard(m_HWND, m_pDXInput);
	}

	~DXInput()
	{
		delete m_pMouse;
		delete m_pKeyboard;

		m_pDXInput->Release();
	}

	/**
	* @brief マウスとキーボードの入力状態の更新を行う,メッセージループの始まりで呼ぶ
	*/
	inline VOID UpdataInputState()
	{
		m_pMouse->UpdataInputState();
		m_pKeyboard->UpdataInputState();
	}

	/**
	* @brief マウスとキーボードの入力状態の保存を行う,メッセージループの終わりで呼ぶ
	*/
	inline VOID StorePrevInputState()
	{
		m_pMouse->StorePrevInputState();
		m_pKeyboard->StorePrevInputState();
	}

	/// <summary>
	/// 引数に渡したボタンが押された瞬間か
	/// </summary>
	/// <param name="key">ボタンの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool MouseIsPressed(int key) const
	{
		return m_pMouse->IsPressed(key);
	}

	inline bool MouseIsHeld(int key) const
	{
		return m_pMouse->IsHeld(key);
	}

	inline bool MouseIsReleased(int key) const
	{
		return m_pMouse->IsReleased(key);
	}

	inline bool MouseIsNeutral(int key) const
	{
		return m_pMouse->IsNeutral(key);
	}

	/// <summary>
	/// 何かのボタンが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool MouseAnyKeyIsPressed() const
	{
		return m_pMouse->AnyKeyIsPressed();
	}

	/// <summary>
	/// カーソルの位置の取得
	/// </summary>
	/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
	inline VOID CursorPos(POINT* pPos) const
	{
		m_pMouse->CursorPos(pPos);
	}

	/// <summary>
	/// 前フレームからどのくらいスクロールされたか
	/// </summary>
	/// <returns>スクロールされた量</returns>
	inline long MouseWheelScrollingFromPrev() const
	{
		return m_pMouse->WheelScrollingFromPrev();
	}

	/// <summary>
	/// 引数に渡したキーが押された瞬間か
	/// </summary>
	/// <param name="key">キーの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool KeyboardIsPressed(int key) const
	{
		return m_pKeyboard->IsPressed(key);
	}

	inline bool KeyboardIsHeld(int key) const
	{
		return m_pKeyboard->IsHeld(key);
	}

	inline bool KeyboardIsReleased(int key) const
	{
		return m_pKeyboard->IsReleased(key);
	}

	inline bool KeyboardIsNeutral(int key) const
	{
		return m_pKeyboard->IsNeutral(key);
	}

	/// <summary>
	/// 何かのキーが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool KeyboardAnyKeyIsPressed() const
	{
		return m_pKeyboard->AnyKeyIsPressed();
	}

private:
	VOID Create()
	{
		DirectInput8Create(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION, IID_IDirectInput8,
			(VOID**)&m_pDXInput,
			NULL);
	}

	const HWND m_HWND = nullptr;

	LPDIRECTINPUT8 m_pDXInput = nullptr;

	Mouse* m_pMouse			= nullptr;
	Keyboard* m_pKeyboard	= nullptr;
};

#endif //! DX_INPUT_H
