/**
* @file D3DPP.h
* @brief バックバッファ関係クラスのヘッダ
*/

#ifndef D3DPP_H
#define D3DPP_H

#include <Windows.h>

#include <d3dx9.h>

#include "../../../Wnd/Data/RectSize.h"

/**
* @brief バックバッファ関係クラス
*/
class D3DPP
{
public:
	D3DPP(HWND hWnd, RectSize wndSize) :m_WND_SIZE(wndSize), m_HWND(hWnd) {};
	~D3DPP() {};

	/**
	* @brief 現在のウィンドウモードのD3DPRESENT_PARAMETERSを返す
	* @return 現在のウィンドウモードのD3DPRESENT_PARAMETERS 
	*/
	inline D3DPRESENT_PARAMETERS GetD3DPRESENT_PARAMETERS()
	{
		D3DPRESENT_PARAMETERS D3DPP;
		InitD3DPP(&D3DPP);

		return D3DPP;
	}

	/**
	* @brief ウィンドウモードを切り替えそのD3DPRESENT_PARAMETERSを返す
	* @return ウィンドウモード切替後のD3DPRESENT_PARAMETERS
	*/
	D3DPRESENT_PARAMETERS ToggleD3DPPWndMode();

private:
	VOID InitD3DPP(D3DPRESENT_PARAMETERS* pD3DPP);

	const HWND m_HWND = nullptr;

	const RectSize m_WND_SIZE;

	bool m_isWindow = true;
};

#endif //! D3DPP_H
