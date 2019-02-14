/// <filename>
/// Mouse.cpp
/// </filename>
/// <summary>
/// マウスクラスのソース
/// </summary>

#include "Mouse.h"

#include <Windows.h>

#include <dinput.h>

#include "Enum/DIM.h"

VOID Mouse::Create(LPDIRECTINPUT8 pDXInput)
{
	pDXInput->CreateDevice(
				GUID_SysMouse,
				&m_pDInputDev,
				NULL);

	m_pDInputDev->SetDataFormat(&c_dfDIMouse);

	m_pDInputDev->SetCooperativeLevel(
					m_HWND,
					DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD mouseProp;
	mouseProp.diph.dwSize		= sizeof(DIPROPDWORD);
	mouseProp.diph.dwHeaderSize = sizeof(mouseProp.diph);
	mouseProp.diph.dwObj		= 0;
	mouseProp.diph.dwHow		= DIPH_DEVICE;
	mouseProp.dwData			= DIPROPAXISMODE_REL;

	m_pDInputDev->SetProperty(DIPROP_AXISMODE, &mouseProp.diph);
}

VOID Mouse::AcquireInputState()
{
	//! マウスの状態を取得する権限の取得
	m_pDInputDev->Acquire();

	//! ここではまだディスプレイ基準の絶対座標
	GetCursorPos(&m_cursorRelativePos);

	//! ここでウィンドウ基準の相対座標に変換
	ScreenToClient(m_HWND, &m_cursorRelativePos);

	//!マウスの状態を取得
	m_pDInputDev->GetDeviceState(
		sizeof(DIMOUSESTATE),
		&m_state);
}

VOID Mouse::CheckInputStateDetatils()
{
	bool isInputtedPrev	= false;
	bool isInputted		= false;

	ZeroMemory(&m_details, sizeof(bool) * DIM_MAX);

	for (int i = 0; i < DIM_MAX; ++i)
	{
		isInputtedPrev	= IsInputted(m_prevState.rgbButtons[i]);
		isInputted		= IsInputted(m_state.rgbButtons[i]);

		if (isInputtedPrev)
		{
			m_details[i] = (isInputted) ? IND_HOLD : IND_RELEASE;

			continue;
		}

		m_details[i] = (isInputted) ? IND_PRESS : IND_NEUTRAL;
	}
}
