/// <filename>
/// DX3D.cpp
/// </filename>
/// <summary>
/// 描画関係クラスのFacadeのソース
/// </summary>

#include "DX3D.h"

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "D3DPP/D3DPP.h"
#include "ColorBlender/ColorBlender.h"
#include "Light/Light.h"
#include "TexStorage/TexStorage.h"
#include "Camera/Camera.h"
#include "CustomVertexEditor/CustomVertexEditor.h"
#include "Renderer/Renderer.h"
#include "FbxStorage/FbxStorage.h"
#include "FontStorage/FontStorage.h"
#include "Wnd/Data/RectSize.h"
#include "CustomVertex.h"
#include "VerticesParam.h"

DX3D::DX3D(HWND hWnd, RectSize wndSize, LPDIRECT3D9 pD3D)
	:m_HWND(hWnd), m_D3DPP(new D3DPP(m_HWND, wndSize))
{
	Create(pD3D);

	m_pDX3DDev->SetRenderState(D3DRS_ZENABLE, true);

	//! コメントアウトしているときはカリングを行うということ(ポリゴンの裏を描画しない)
	//m_pDX3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pColorBlender = new ColorBlender(m_pDX3DDev);
	m_pColorBlender->DefaultColorBlending();

	m_pLight = new Light(m_pDX3DDev);
	m_pLight->DefaultLighting();

	m_pTexStorage = new TexStorage(m_pDX3DDev);

	m_pCamera = new Camera(m_pDX3DDev);

	m_pCustomVertex = new CustomVertexEditor(m_pDX3DDev);

	m_pRenderer = new Renderer(m_pDX3DDev);

	m_pFbxStorage = new FbxStorage(m_pDX3DDev);

	m_pFont = new FontStorage(m_pDX3DDev);

	InitViewPort();
}

void DX3D::PrepareRendering() const
{
	m_pDX3DDev->Clear(
		0,
		NULL,

		//! 3DなのでZBUFFERもクリア
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,

		//! 画面をクリアするときの色
		D3DCOLOR_XRGB(0, 0, 0),
		1.f,
		0);

	m_pDX3DDev->BeginScene();
}

void DX3D::CleanUpRendering() const
{
	m_pDX3DDev->EndScene();
	m_pDX3DDev->Present(
		NULL,
		NULL,
		NULL,
		NULL);
}

void DX3D::ToggleWndMode()
{
	D3DPRESENT_PARAMETERS D3DPP = m_D3DPP->ToggleD3DPPWndMode();

	//! スワップチェーンのタイプ、サイズ、およびフォーマットをリセット
	HRESULT hr = m_pDX3DDev->Reset(&D3DPP);

	InvalidateRect(m_HWND, NULL, false);
	UpdateWindow(nullptr);

	if (FAILED(hr))
	{
		OnFailedChangeWndMode(hr);

		return;
	}

	RedrawWindow(m_HWND, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	long overlapWindowStyle	= (D3DPP.Windowed) ? WS_OVERLAPPEDWINDOW : WS_POPUP;
	long windowStyle		= overlapWindowStyle | WS_VISIBLE;

	SetWindowLong(
		m_HWND,
		GWL_STYLE,
		windowStyle);

	m_pColorBlender->DefaultColorBlending();

	InitViewPort();

}

void DX3D::Create(LPDIRECT3D9 pD3D)
{
	D3DPRESENT_PARAMETERS D3DPP = m_D3DPP->GetD3DPRESENT_PARAMETERS();

	if (SUCCEEDED(pD3D->CreateDevice(	
						//! 描画をハードウェアに依存させる 軽い
						D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
						m_HWND,
						D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
						&D3DPP,
						&m_pDX3DDev)))
	{
		return;
	}

	MessageBox(
		0, 
		_T("HALモードでDIRECT3Dデバイスを作成できません/nREFモードで再試行します"),
		NULL, 
		MB_OK);

	if (SUCCEEDED(pD3D->CreateDevice(	
						//! 描画をソフトウェアに依存させる 重い
						D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
						m_HWND,
						D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
						&D3DPP,
						&m_pDX3DDev)))
	{
		return;
	}

	MessageBox(
		0,
		_T("DIRECT3Dデバイスの作成に失敗しました"),
		NULL, 
		MB_OK);

	//! WM_DESTROYをWndProcに投げる
	DestroyWindow(m_HWND);	
}

void DX3D::OnFailedChangeWndMode(HRESULT resetRetVal)
{
	if (resetRetVal == D3DERR_DEVICELOST)
	{
		return;				//デバイスがロストとしたときの対処
	}

	DestroyWindow(m_HWND);	//WM_DESTROYをWndProcに投げる
}

inline void DX3D::InitViewPort()
{
	D3DPRESENT_PARAMETERS D3DPP = m_D3DPP->GetD3DPRESENT_PARAMETERS();

	D3DVIEWPORT9 viewPort;
	viewPort.Width	= D3DPP.BackBufferWidth;
	viewPort.Height = D3DPP.BackBufferHeight;
	viewPort.MinZ	= 0.0f;
	viewPort.MaxZ	= 1.0f;
	viewPort.X		= 0;
	viewPort.Y		= 0;
	m_pDX3DDev->SetViewport(&viewPort);
}
