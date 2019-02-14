/**
* @file CustomVertexEditor.h
* @brief 頂点データ構造体の編集を行うクラスのヘッダ
*/

#ifndef CUSTOM_VERTEX_EDITOR_H
#define CUSTOM_VERTEX_EDITOR_H

#include <Windows.h>

#include <d3dx9.h>

#include "Data/CustomVertex.h"
#include "Data/VerticesParam.h"

/**
* @brief 頂点データ構造体とその構造体の編集を行うクラス
*/
class CustomVertexEditor
{
public:
	explicit CustomVertexEditor(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~CustomVertexEditor() {};

	/**
	* @brief XYZ順に回転を行う
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param deg 回転をさせる度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	* @detail 回転行列を作成し、矩形の中心を求め回転の中心を原点に移動させ、回転行列を用いて回転を行い原点へ移動させた分元に戻す
	*/
	VOID RotateXYZ(CustomVertex* pCustomVertices, const RotateValueXYZ& deg, const D3DXVECTOR3& relativeRotateCenter) const;
	VOID RotateXYZ(CustomVertex* pCustomVertices, const RotateValueXYZ& deg) const;

	/**
	* @brief x軸で回転させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param 度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	*/
	VOID RotateX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const;
	VOID RotateY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const;
	VOID RotateZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const;

	/**
	* @brief 矩形を拡縮させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param scaleRate 拡縮率
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	VOID Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const;

	/**
	* @brief 矩形を移動させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param movement 移動量
	*/
	VOID Move(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const;

	/**
	* @brief 矩形を引数の位置に再配置させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param pos 矩形を移動させる座標
	*/
	VOID Locale(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const;

	/**
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param startTU x方向のテクスチャ座標の始まりの値
	* @param startTV y方向のテクスチャ座標の始まりの値
	* @param endTU x方向のテクスチャ座標の終わりの値
	* @param endTV y方向のテクスチャ座標の終わりの値
	*/
	VOID SetTexUV(CustomVertex* pCustomVertices, float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const;

	/**
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param aRGB アルファ値入りのカラーコード ARGB
	*/
	VOID SetARGB(CustomVertex *pCustomVertices, DWORD aRGB) const;

	/// <summary>
	/// 矩形を上から下にグラデーションさせる
	/// </summary>
	/// <param name="pCustomVertices">[out]グラデーションさせたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="topARGB">上の色</param>
	/// <param name="bottomARGB">下の色</param>
	VOID SetTopBottomARGB(CustomVertex* pCustomVertices, DWORD topARGB, DWORD bottomARGB) const;
	VOID SetLeftRightARGB(CustomVertex* pCustomVertices, DWORD leftARGB, DWORD rightARGB) const;
	VOID SetObliqueToBottomRightARGB(CustomVertex* pCustomVertices, DWORD topARGB, DWORD bottomARGB) const;
	VOID SetObliqueToBottomLeftARGB(CustomVertex* pCustomVertices, DWORD topARGB, DWORD bottomARGB) const;

	/// <summary>
	/// 矩形を点滅させる
	/// </summary>
	/// <param name="pVertices">[out]点滅させたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="pFrameCnt">
	/// [in,out]点滅の強度を決めるためのカウント
	/// 関数内で自動で増減させるのでstaticかつ関数外で値を変えてはいけない
	/// </param>
	/// <param name="flashFlameMax">何フレームで一周期を終えるか</param>
	/// <param name="alphaMax">アルファ値の最大値</param>
	/// <param name="alphaMin">アルファ値の最小値</param>
	VOID Flash(CustomVertex* pVertices, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const;

	/**
	* @brief 頂点データ構造体を引数の値から作成する
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param center 矩形の中心
	* @param halfScale 矩形の高さ幅の半分
	* @param aRGB 頂点の色カラーコード
	* @param startTU x方向のテクスチャ座標の始まりの値
	* @param startTV y方向のテクスチャ座標の始まりの値
	* @param endTU x方向のテクスチャ座標の終わりの値
	* @param endTV y方向のテクスチャ座標の終わりの値
	*/
	VOID Create(CustomVertex* pCustomVertices, const D3DXVECTOR3& center, const D3DXVECTOR3& halfScale,
		DWORD aRGB = 0xFFFFFFFF, float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const;

	/**
	* @brief 頂点データ構造体を引数の値から作成する 回転も行う
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param verticesParam オブジェクトの状態構造体
	*/
	VOID Create(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const;

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;

	static const int m_RECT_VERTICES_NUM = 4;	//! 矩形を構成する頂点の数

	VOID Rotate(CustomVertex* pCustomVertices, const D3DXVECTOR3& relativeRotateCenter, const D3DXMATRIX& rRotate) const;

	VOID SetAverageARGB(DWORD* averageARGB, DWORD aARGB, DWORD bARGB) const;
};

#endif //! CUSTOM_VERTEX_EDITOR_H
