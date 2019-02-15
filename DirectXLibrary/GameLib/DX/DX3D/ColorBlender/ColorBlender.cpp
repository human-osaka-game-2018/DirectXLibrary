/// <filename>
/// ColorBlender.cpp
/// </filename>
/// <summary>
/// 色の合成クラスのソース
/// </summary>

#include "ColorBlender.h"

#include <Windows.h>

#include <d3dx9.h>

void ColorBlender::DefaultColorBlending() const
{
	DefaultBlendMode();
	m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//!	アルファ値が0x01以下の部分を描画しない
	m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_ALPHAREF, 0x01);
	
	m_pDX_GRAPHIC_DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDX_GRAPHIC_DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	
	m_pDX_GRAPHIC_DEVICE->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDX_GRAPHIC_DEVICE->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
}
