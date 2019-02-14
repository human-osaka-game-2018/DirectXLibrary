/**
* @file Wnd.h
* @brief ウィンドウクラスのヘッダ
*/

#ifndef WND_H
#define WND_H

#include <Windows.h>

#include "Data/RectSize.h"

/**
* @brief ウィンドウクラス
*/
class Wnd
{
public:
	Wnd(const HINSTANCE hInst, const TCHAR* pAppName);
	~Wnd() {};

	/**
	* @brief ウィンドウハンドルを取得する
	* @return ウィンドウハンドル
	*/
	inline const HWND GetHWND() const
	{
		return m_hWnd;
	}

	/**
	* @brief WinMessageの構造体を取得する
	* @return WinMessageの構造体
	*/
	inline MSG GetMSG() const
	{
		return m_msg;
	}

	/**
	* @brief ウィンドウのサイズを取得する
	* @return ウィンドウのサイズ
	*/
	inline RectSize GetWndSize() const
	{
		return m_WND_SIZE;
	}

	/**
	* @brief ウィンドウを終了するメッセージが投げられたか
	* @return 投げられていたらtrue
	*/
	inline bool IsPostedQuitMessage() const
	{
		if (m_msg.message == WM_QUIT) return true;

		return false;
	}

	/**
	* @brief WinMessageが何かあるか
	* @return あればtrue
	*/
	bool ExistsWinMSG();

	/**
	* @brief クライアント領域をm_WND_SIZEと同じにする
	*/
	VOID ResizeWnd() const;

private:
	VOID Create(const HINSTANCE hInst, const TCHAR* pAppName);

	/// <summary>
	/// ウィンドウを生成するときにProcの関数ポインタが必要なのでstatic
	/// </summary>
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);    
																							
	//! IDX3D経由でDX3DのメソッドToggleWndMode()を呼ぶ
	HWND m_hWnd = nullptr;

	MSG m_msg;

	const RectSize m_WND_SIZE = { 1280, 720 };
};

#endif // !WND_H
