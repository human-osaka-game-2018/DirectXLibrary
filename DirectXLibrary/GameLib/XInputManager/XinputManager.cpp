/// <summary>
/// XinputManager関連処理
/// </summary>
/**
* @author Toshiya Matsuoka
*/
#include "XinputManager.h"

using namespace Xinput;

XinputManager::XinputManager()
{
	m_pXinputDevice[PLAYER_01] = new XinputDevice(PLAYER_01);
	m_pXinputDevice[PLAYER_02] = new XinputDevice(PLAYER_02);
	m_pXinputDevice[PLAYER_03] = new XinputDevice(PLAYER_03);
	m_pXinputDevice[PLAYER_04] = new XinputDevice(PLAYER_04);

}


XinputManager::~XinputManager()
{
	delete m_pXinputDevice[PLAYER_01];
	delete m_pXinputDevice[PLAYER_02];
	delete m_pXinputDevice[PLAYER_03];
	delete m_pXinputDevice[PLAYER_04];

}

void XinputManager::DeviceUpdate()
{
	m_pXinputDevice[PLAYER_01]->DeviceUpdate();
	m_pXinputDevice[PLAYER_02]->DeviceUpdate();
	m_pXinputDevice[PLAYER_03]->DeviceUpdate();
	m_pXinputDevice[PLAYER_04]->DeviceUpdate();
}

int XinputManager::GetAnalogTrigger(Xinput::AnalogTrigger Trigger, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return 0;
	return m_pXinputDevice[num]->GetAnalogTrigger(Trigger);
}

bool XinputManager::GetAnalogL(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return 0;
	return m_pXinputDevice[num]->GetAnalogL(AnalogState);
}

bool XinputManager::GetAnalogR(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return 0;
	return m_pXinputDevice[num]->GetAnalogR(AnalogState);
}

int XinputManager::GetAnalogLValue(Xinput::AnalogAxis AnalogState, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return 0;
	return m_pXinputDevice[num]->GetAnalogLValue(AnalogState);
}

int XinputManager::GetAnalogRValue(Xinput::AnalogAxis AnalogState, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return 0;
	return m_pXinputDevice[num]->GetAnalogRValue(AnalogState);
}

Xinput::PADSTATE XinputManager::GetAnalogLState(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return PadOff;
	return m_pXinputDevice[num]->GetAnalogLState(AnalogState);
}

Xinput::PADSTATE XinputManager::GetAnalogRState(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return PadOff;
	return m_pXinputDevice[num]->GetAnalogRState(AnalogState);
}

Xinput::PADSTATE XinputManager::GetTriggerRState(Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return PadOff;
	return m_pXinputDevice[num]->GetTriggerRState();
}

Xinput::PADSTATE XinputManager::GetTriggerLState(Xinput::PLAYER_NUM num)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return PadOff;
	return m_pXinputDevice[num]->GetTriggerLState();
}

void XinputManager::RunVibration(Xinput::PLAYER_NUM num, unsigned int LeftValue, unsigned int RightValue)
{
	if (ERROR_SUCCESS != m_pXinputDevice[num]->GetInfo()) return;
	m_pXinputDevice[num]->RunVibration(LeftValue, RightValue);
}

