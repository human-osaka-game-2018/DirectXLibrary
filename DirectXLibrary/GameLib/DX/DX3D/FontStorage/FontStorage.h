/// <filename>
/// FontStorage.h
/// </filename>
/// <summary>
/// フォントの保管を行うクラスのヘッダ
/// </summary>

#ifndef FONT_STORAGE_H
#define FONT_STORAGE_H

#include <Windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

/// <summary>
/// フォントの保管を行うクラス
/// </summary>
class FontStorage
{
public:
	FontStorage(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};

	~FontStorage() 
	{
		AllRelease();
	}

	/// <summary>
	/// フォントの全開放
	/// </summary>
	inline VOID AllRelease()
	{
		for (auto i : m_fonts)
		{
			i.second->Release();
		}
	}

	/// <summary>
	/// 指定したフォントの開放
	/// </summary>
	/// <param name="pFontKey">開放したいフォントのキー</param>
	inline VOID Release(const TCHAR* pFontKey)
	{
		if (!Exists(pFontKey)) return;

		m_fonts[pFontKey]->Release();
		m_fonts.erase(pFontKey);
	}

	/// <summary>
	///	フォントオブジェクトの作成
	/// </summary>
	/// <param name="pKey">作成するオブジェクトにつけるキー</param>
	/// <param name="scale">文字の幅</param>
	/// <param name="pFontName">フォントの名前 MSゴシック等</param>
	/// <param name="thickness">文字の太さ</param>
	VOID Create(const TCHAR* pKey, D3DXVECTOR2 scale, const TCHAR* pFontName, UINT thickness = 0);

	/// <summary>
	/// 文字が存在しているかを判別する
	/// </summary>
	/// <param name="pKey">判別したいフォントのキー</param>
	/// <returns>存在していればtrue</returns>
	inline bool Exists(const TCHAR* pKey)
	{
		return (m_fonts.find(pKey) != m_fonts.end());
	}

	/// <summary>
	/// フォントオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">取得したいフォントのキー</param>
	/// <returns>フォントオブジェクトの参照</returns>
	inline const LPD3DXFONT GetFont(const TCHAR* pKey)
	{
		return m_fonts[pKey];
	}

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;

	std::map<const TCHAR*, LPD3DXFONT> m_fonts;
};

#endif //! FONT_STORAGE_H
