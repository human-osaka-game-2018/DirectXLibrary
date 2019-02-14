/// <filename>
/// FontStorage.cpp
/// </filename>
/// <summary>
/// フォントの保管を行うクラスのソース
/// </summary>

#include "FontStorage.h"

#include <Windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

VOID FontStorage::Create(const TCHAR* pKey, D3DXVECTOR2 scale, const TCHAR* pFontName, UINT thickness)
{
	if (Exists(pKey)) return;

	D3DXCreateFont(
		m_pDX_GRAPHIC_DEVICE,
		static_cast<int>(scale.y), static_cast<int>(scale.x),
		thickness,
		0,
		0,
		//! 日本語を表示するのでキャラセットを固定
		SHIFTJIS_CHARSET,
		0,
		0,
		0,
		pFontName,
		&m_fonts[pKey]);
}
