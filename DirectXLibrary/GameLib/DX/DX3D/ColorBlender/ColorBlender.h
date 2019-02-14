/**
* @file ColorBlender.h
* @brief 色の合成クラスのヘッダ
*/

#ifndef COLOR_BLENDER_H
#define COLOR_BLENDER_H

#include <Windows.h>

#include <d3dx9.h>

/**
* @brief 色の合成を変更するクラス
*/
class ColorBlender
{
public:
	ColorBlender(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~ColorBlender() {};

	/**
	* @brief 色の合成を通常合成に変更する デフォルトでは通常合成になっている
	*/
	inline VOID DefaultBlendMode() const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	/**
	* @brief 色の合成を加算合成に変更する
	*/
	inline VOID AddtionBlendMode() const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	/**
	* @brief デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	VOID DefaultColorBlending() const;

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;
};

#endif //!　COLOR_BLENDER_H
