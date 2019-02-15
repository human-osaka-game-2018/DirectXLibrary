/// <filename>
/// Keyboard.cpp
/// </filename>
/// <summary>
/// キーボードクラスのソース
/// </summary>

#include "Keyboard.h"

#include <Windows.h>

#include <dinput.h>

void Keyboard::Create(LPDIRECTINPUT8 pDXInput)
{
	pDXInput->CreateDevice(
				GUID_SysKeyboard, &m_pDInputDev,
				NULL);

	m_pDInputDev->SetDataFormat(&c_dfDIKeyboard);

	m_pDInputDev->SetCooperativeLevel(
					m_HWND,
					DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}

void Keyboard::CheckInputStateDetatils()
{
	bool isInputtedPrev	= false;
	bool isInputted		= false;

	const int KEYBOARD_KEYS_MAX = 256;
	ZeroMemory(m_details, sizeof(bool) * KEYBOARD_KEYS_MAX);

	for (int i = 0; i < KEYBOARD_KEYS_MAX; ++i)
	{
		isInputtedPrev	= IsInputted(m_prevDiks[i]);
		isInputted		= IsInputted(m_diks[i]);

		if (isInputtedPrev)
		{
			m_details[i] = (isInputted) ? IND_HOLD : IND_RELEASE;

			continue;
		}

		m_details[i] = (isInputted) ? IND_PRESS : IND_NEUTRAL;
	}
}
