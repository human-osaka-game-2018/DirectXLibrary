/**
* @file Renderer.h
* @brief 描画クラスのヘッダ
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>

#include <d3dx9.h>

#include "CustomVertex.h"
#include "VerticesParam.h"
#include "3DBoard\3DBoard.h"
#include "DX\DX3D\FbxStorage\FbxStorage.h"

/**
* @brief FBXとCustomVertexの描画クラス
*/
class Renderer
{
public:
	Renderer(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~Renderer() {};

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	void Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const;

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	void Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const;

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	void Render(const Vertex3D* pVertex, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr)const ;

	/// <summary>
	/// 文字の描画を行う
	/// </summary>
	/// <param name="topLeft">[in]左上の座標</param>
	/// <param name="pText">[in]描画したい文字列</param>
	/// <param name="format">文字のフォーマット DT_LEFT(左寄せ)等</param>
	/// <param name="pFont">描画する際に使うフォントオブジェクト</param>
	/// <param name="color">文字の色ARGB</param>
	void Render(const D3DXVECTOR2& topLeft, const TCHAR* pText, UINT format, LPD3DXFONT pFont, DWORD color) const;

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;
};

#endif //! RENDERER_H
