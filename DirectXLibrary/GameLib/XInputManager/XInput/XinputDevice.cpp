﻿/// <summary>
/// XinputDevice関連処理
/// </summary>
/**
* @author Toshiya Matsuoka
*/

#include "XinputDevice.h"

using namespace Xinput;


XinputDevice::XinputDevice(PLAYER_NUM number) :ControlerNum(number)
{
}

void XinputDevice::GetControl()
{
	XINPUT_INFO = XInputGetState(ControlerNum, &m_Xinput);
}

PADSTATE XinputDevice::GetButton(ButtonIndex index)const
{
	return m_PadState[index];
}

void XinputDevice::BottonCheck() {

	CheckButtonState(XINPUT_GAMEPAD_A, ButtonA);
	CheckButtonState(XINPUT_GAMEPAD_B, ButtonB);
	CheckButtonState(XINPUT_GAMEPAD_X, ButtonX);
	CheckButtonState(XINPUT_GAMEPAD_Y, ButtonY);
	CheckButtonState(XINPUT_GAMEPAD_START, ButtonStart);
	CheckButtonState(XINPUT_GAMEPAD_BACK, ButtonBack);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_SHOULDER, ButtonLB);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_SHOULDER, ButtonRB);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_UP, ButtonUP);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_DOWN, ButtonDOWN);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_LEFT, ButtonLEFT);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, ButtonRIGHT);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_THUMB, ButtonLeftThumb);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_THUMB, ButtonRightThumb);

	AnalogLStateDivide(ANALOGUP);
	AnalogRStateDivide(ANALOGUP);
	AnalogLStateDivide(ANALOGDOWN);
	AnalogRStateDivide(ANALOGDOWN);
	AnalogLStateDivide(ANALOGLEFT);
	AnalogRStateDivide(ANALOGLEFT);
	AnalogLStateDivide(ANALOGRIGHT);
	AnalogRStateDivide(ANALOGRIGHT);

	TriggerRStateDivide();
	TriggerLStateDivide();
}

void XinputDevice::DeviceUpdate() {

	GetControl();
	BottonCheck();
}

void XinputDevice::CheckButtonState(WORD ButtomID, ButtonIndex ButtomIndex)
{
	if (m_Xinput.Gamepad.wButtons & ButtomID)
	{
		if (m_PadOldState[ButtomIndex] == PadOn)
		{
			m_PadState[ButtomIndex] = PadOn;
		}
		else
		{
			m_PadState[ButtomIndex] = PadPush;
		}

		m_PadOldState[ButtomIndex] = PadOn;
	}
	else
	{
		if (m_PadOldState[ButtomIndex] == PadOn)
		{
			m_PadState[ButtomIndex] = PadRelease;
		}
		else
		{
			m_PadState[ButtomIndex] = PadOff;
		}
		m_PadOldState[ButtomIndex] = PadOff;
	}
}

int XinputDevice::GetAnalogTrigger(AnalogTrigger Trigger)const
{
	switch (Trigger)
	{
	case LEFT_TRIGGER:
		return m_Xinput.Gamepad.bLeftTrigger;
	case RIGHT_TRIGGER:
		return m_Xinput.Gamepad.bRightTrigger;
	}
	return 0;
}

bool XinputDevice::GetAnalogL(Analog AnalogState)const
{
	switch (AnalogState)
	{
	case ANALOGUP:
		if (GetAnalogLValue(ANALOG_Y) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (GetAnalogLValue(ANALOG_Y) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (GetAnalogLValue(ANALOG_X) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (GetAnalogLValue(ANALOG_X) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

bool XinputDevice::GetAnalogR(Analog AnalogState)const
{
	switch (AnalogState)
	{
	case ANALOGUP:
		if (GetAnalogRValue(ANALOG_Y) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (GetAnalogRValue(ANALOG_Y) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (GetAnalogRValue(ANALOG_X) > INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (GetAnalogRValue(ANALOG_X) < -INCLINATION_THRESHOLD_VALUE)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

int XinputDevice::GetAnalogLValue(AnalogAxis AnalogState)const
{
	switch (AnalogState)
	{
	case ANALOG_Y:
		return m_Xinput.Gamepad.sThumbLY;
		break;
	case ANALOG_X:
		return m_Xinput.Gamepad.sThumbLX;
		break;
	default:
		return 0;
	}
}

int XinputDevice::GetAnalogRValue(AnalogAxis AnalogState)const
{
	switch (AnalogState)
	{
	case ANALOG_Y:
		return m_Xinput.Gamepad.sThumbRY;
		break;
	case ANALOG_X:
		return m_Xinput.Gamepad.sThumbRX;
		break;
	default:
		return 0;
	}
}

PADSTATE XinputDevice::GetAnalogLState(Analog AnalogState)const
{
	return m_AnalogLState[AnalogState];
}

PADSTATE XinputDevice::GetAnalogRState(Analog AnalogState)const
{
	return m_AnalogRState[AnalogState];
}

PADSTATE XinputDevice::GetTriggerRState()const
{
	return m_TriggerRState;
}

PADSTATE XinputDevice::GetTriggerLState()const
{
	return m_TriggerLState;
}

void XinputDevice::AnalogRStateDivide(Analog AnalogState) {
	if (GetAnalogR(AnalogState))
	{
		if (m_AnalogROldState[AnalogState] == PadOn)
		{
			m_AnalogRState[AnalogState] = PadOn;
		}
		else
		{
			m_AnalogRState[AnalogState] = PadPush;
		}
		m_AnalogROldState[AnalogState] = PadOn;
	}
	else
	{
		if (m_AnalogROldState[AnalogState] == PadOn)
		{
			m_AnalogRState[AnalogState] = PadRelease;
		}
		else
		{
			m_AnalogRState[AnalogState] = PadOff;
		}
		m_AnalogROldState[AnalogState] = PadOff;
	}
}

void XinputDevice::AnalogLStateDivide(Analog AnalogState) {
	if (GetAnalogL(AnalogState))
	{
		if (m_AnalogLOldState[AnalogState] == PadOn)
		{
			m_AnalogLState[AnalogState] = PadOn;
		}
		else
		{
			m_AnalogLState[AnalogState] = PadPush;
		}
		m_AnalogLOldState[AnalogState] = PadOn;
	}
	else
	{
		if (m_AnalogLOldState[AnalogState] == PadOn)
		{
			m_AnalogLState[AnalogState] = PadRelease;
		}
		else
		{
			m_AnalogLState[AnalogState] = PadOff;
		}
		m_AnalogLOldState[AnalogState] = PadOff;
	}
}

void XinputDevice::TriggerRStateDivide() {
	if (GetAnalogTrigger(RIGHT_TRIGGER))
	{
		if (m_TriggerROldState == PadOn)
		{
			m_TriggerRState = PadOn;
		}
		else
		{
			m_TriggerRState = PadPush;
		}
		m_TriggerROldState = PadOn;
	}
	else
	{
		if (m_TriggerROldState == PadOn)
		{
			m_TriggerRState = PadRelease;
		}
		else
		{
			m_TriggerRState = PadOff;
		}
		m_TriggerROldState = PadOff;
	}
}
void XinputDevice::TriggerLStateDivide() {
	if (GetAnalogTrigger(LEFT_TRIGGER))
	{
		if (m_TriggerLOldState == PadOn)
		{
			m_TriggerLState = PadOn;
		}
		else
		{
			m_TriggerLState = PadPush;
		}
		m_TriggerLOldState = PadOn;
	}
	else
	{
		if (m_TriggerLOldState == PadOn)
		{
			m_TriggerLState = PadRelease;
		}
		else
		{
			m_TriggerLState = PadOff;
		}
		m_TriggerLOldState = PadOff;
	}
}

void XinputDevice::RunVibration(unsigned int LeftValue, unsigned int RightValue) {
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = LeftValue;
	vibration.wRightMotorSpeed = RightValue;
	XInputSetState(ControlerNum, &vibration);
}

