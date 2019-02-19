/// <filename>
/// GameLib.cpp
/// </filename>
/// <summary>
/// 汎用クラスのFacadeのソース
/// </summary>

#include "GameLib.h"

#include <Windows.h>

#include <d3dx9.h>

#include "IGameLibRenderer\IGameLibRenderer.h"
#include "../Class/Singleton/Singleton.h"
#include "Wnd\Wnd.h"
#include "DX\DX.h"
#include "CustomVertex.h"
#include "VerticesParam.h"
#include "TimerManager\TimerManager.h"
#include "Collision\Collision.h"
#include "3DBoard\3DBoard.h"
#include "Sound\Sound.h"
#include "JoyconManager\JoyconManager.h"
#include "EffectManager\EffectManager.h"

#include <crtdbg.h>

#include <cstdio>
#include <cstdlib>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

Wnd* GameLib::m_pWnd = nullptr;

DX* GameLib::m_pDX = nullptr;

Collision* GameLib::m_pCollision = nullptr;

Board3D* GameLib::m_pBoard3D = nullptr;

Sound* GameLib::m_pSound = nullptr;

JoyconManager* GameLib::m_pJoyconManager = nullptr;

EffectManager* GameLib::m_pEffectManager = nullptr;

XinputManager* GameLib::m_pXinputManager = nullptr;

void GameLib::RunFunc(void(*pMainFunc)())
{
	while (!m_pWnd->IsPostedQuitMessage())
	{
		if (m_pWnd->ExistsWinMSG()) continue;

		if (!m_rTimerManager.CanStartNextFrame()) continue;

		m_pDX->PrepareMessageLoop();

		m_pJoyconManager->InputState();
		m_pXinputManager->DeviceUpdate();

		pMainFunc();

		m_pEffectManager->Update();
		m_pEffectManager->Render();

		m_pDX->CleanUpMessageLoop();
	}
}
