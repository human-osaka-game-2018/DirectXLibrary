/// <filename>
/// Collision.h
/// </filename>
/// <summary>
/// 衝突判定関数をまとめたクラスのヘッダ
/// </summary>

#ifndef COLLISION_H
#define COLLISION_H

#include <Windows.h>

#include <d3dx9.h>

#include "CustomVertex.h"

/// <summary>
/// 衝突判定関数をまとめたクラス
/// </summary>
class Collision
{
public:
	Collision() {}

	Collision(const Collision&) = delete;
	Collision& operator=(const Collision&) = delete;

	~Collision() {}

	/// <summary>
	/// 円と円の衝突判定を返す、衝突していればtrue
	/// </summary>
	/// <param name="pAPos">[in]片方の円の位置</param>
	/// <param name="pBPos">[in]もう片方の円の位置</param>
	/// <param name="aRadius">片方の円の半径</param>
	/// <param name="bRadius">もう片方の円の位置</param>
	/// <returns>衝突していればtrue</returns>
	bool CollidesCircles(const D3DXVECTOR3* pACenter, const D3DXVECTOR3* pBCenter, float aRadius, float bRadius) const;

	/// <summary>
	/// 円と円の衝突判定を返す、衝突していればtrue
	/// </summary>
	/// <param name="pA">[in]片方の円の頂点情報配列の先頭アドレス</param>
	/// <param name="pB">[in]もう片方の円の頂点情報配列の先頭アドレス</param>
	/// <returns>衝突していればtrue</returns>
	bool CollidesCircles(const CustomVertex* pA, const CustomVertex* pB) const;

	/// <summary>
	/// 矩形と矩形の衝突判定を返す、衝突していればtrue
	/// </summary>
	/// <param name="pA">[in]片方の矩形の頂点情報配列の先頭アドレス</param>
	/// <param name="pB">[in]もう片方の矩形の頂点情報配列の先頭アドレス</param>
	/// <returns>衝突していればtrue</returns>
	bool CollidesRects(const CustomVertex* pA, const CustomVertex* pB) const;
};

#endif //! COLLISION_H
