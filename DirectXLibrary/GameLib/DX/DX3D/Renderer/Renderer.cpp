/// <filename>
/// Renderer.cpp
/// </filename>
/// <summary>
/// 描画クラスのソース
/// </summary>

#include "Renderer.h"

#include <Windows.h>

#include <d3dx9.h>

#include "CustomVertex.h"
#include "VerticesParam.h"
#include "3DBoard\3DBoard.h"
#include "DX\DX3D\FbxStorage\FbxStorage.h"

VOID Renderer::Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture) const
{
	m_pDX_GRAPHIC_DEVICE->SetTransform(D3DTS_WORLD, &rWorld);

	m_pDX_GRAPHIC_DEVICE->SetTexture(0, pTexture);

	for (FbxModel* pI : rFBXModel.m_pModel)
	{
		pI->DrawFbx();
	}
}

VOID Renderer::Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture) const
{
	m_pDX_GRAPHIC_DEVICE->SetFVF(
		D3DFVF_XYZRHW |
		D3DFVF_DIFFUSE |
		D3DFVF_TEX1);

	m_pDX_GRAPHIC_DEVICE->SetTexture(0, pTexture);

	m_pDX_GRAPHIC_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pCustomVertices, sizeof(CustomVertex));
}

VOID Renderer::Render(const Vertex3D* pVertex, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture) const
{
	LPDIRECT3DVERTEXBUFFER9 pBuffer = nullptr;

	m_pDX_GRAPHIC_DEVICE->SetTransform(D3DTS_WORLD, &rWorld);

	m_pDX_GRAPHIC_DEVICE->CreateVertexBuffer(
		4 * sizeof(Vertex3D),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
		D3DPOOL_MANAGED,
		&pBuffer,
		NULL);

	m_pDX_GRAPHIC_DEVICE->SetStreamSource(0, pBuffer, 0, sizeof(Vertex3D));

	m_pDX_GRAPHIC_DEVICE->SetTexture(0, pTexture);

	m_pDX_GRAPHIC_DEVICE->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

	//! 頂点バッファはグラボのメモリに書き込むので開放必須
	pBuffer->Release();
}

VOID Renderer::Render(const D3DXVECTOR2& topLeft, const TCHAR* pText, UINT format, LPD3DXFONT pFont, DWORD color) const
{
	RECT rect;
	SetRectEmpty(&rect);

	//! ここでは矩形を作成しているだけで描画はしていない
	pFont->DrawText(NULL, pText, -1, &rect, format | DT_CALCRECT, color);

	OffsetRect(&rect, static_cast<int>(topLeft.x), static_cast<int>(topLeft.y));

	pFont->DrawText(NULL, pText, -1, &rect, format, color);
}
