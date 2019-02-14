/// <filename>
/// Wnd.cpp
/// </filename>
/// <summary>
/// ウィンドウクラスのソース
/// </summary>

#include "Wnd.h"

#include <Windows.h>

#include "Data/RectSize.h"

Wnd::Wnd(const HINSTANCE hInst, const TCHAR* pAppName)
{
	ZeroMemory(&m_msg, sizeof(MSG));

	Create(hInst, pAppName);
}

bool Wnd::ExistsWinMSG()
{
	if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);

		return true;
	}

	return false;
}

VOID Wnd::Create(const HINSTANCE hInst, const TCHAR* pAppName)
{
	WNDCLASSEX wndclass;
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInst;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= pAppName;
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	m_hWnd = CreateWindow(
				pAppName,pAppName,
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, 
				(int)m_WND_SIZE.m_x, (int)m_WND_SIZE.m_y, 
				NULL, NULL, 
				hInst,
				NULL);

	ResizeWnd();

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return;
}

VOID Wnd::ResizeWnd() const
{
	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	RectSize clientSize = {
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top };

	if (clientSize.m_y == m_WND_SIZE.m_y) return;

	RECT wndRect;
	GetWindowRect(m_hWnd, &wndRect);

	RectSize wndSize = {
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top };

	RectSize frameSize = {
		wndSize.m_x - clientSize.m_x,
		wndSize.m_y - clientSize.m_y };

	SetWindowPos(
		m_hWnd,
		NULL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_WND_SIZE.m_x + frameSize.m_x,
		m_WND_SIZE.m_y + frameSize.m_y,
		SWP_NOMOVE);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

LRESULT CALLBACK Wnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	//! ウィンドウの終了ボタンが押された時
	case WM_DESTROY:										
		//! プログラムの終了メッセージを投げる
		PostQuitMessage(0);									

		break;

	//! Alt + 特殊キーの処理に使う
	case WM_SYSKEYDOWN:										
		//! プログラムの終了メッセージを投げる
		if (wParam == VK_BACK) PostQuitMessage(0);			
	
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
