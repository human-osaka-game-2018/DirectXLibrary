/// <filename>
/// Collision.cpp
/// </filename>
/// <summary>
/// 衝突判定関数をまとめたクラスのソース
/// </summary>

#include "Collision.h"

#include <Windows.h>

#include <d3dx9.h>

#include "CustomVertex.h"

bool Collision::CollidesCircles(const D3DXVECTOR3* pACenter, const D3DXVECTOR3* pBCenter, float aRadius, float bRadius) const
{
	//! 円と円の当たり判定なのでZ値を無視する
	D3DXVECTOR2 APos(pACenter->x, pACenter->y);
	D3DXVECTOR2 BPos(pBCenter->x, pBCenter->y);

	D3DXVECTOR2 aBDistanceVec = APos - BPos;
	float aBDistance = D3DXVec2Length(&aBDistanceVec);

	if (aBDistance <= aRadius + bRadius) return true;

	return false;
}

bool Collision::CollidesCircles(const CustomVertex* pA, const CustomVertex* pB) const
{
	/// <summary>
	/// 矩形から円の半径と中心を作成するラムダ
	/// </summary>
	/// <param name="pVertices">[in]矩形の頂点情報配列の先頭アドレス</param>
	/// <param name="pRadius">[out]円の半径</param>
	/// <param name="pCenter">[out]円の中心</param>
	auto FormatRectToCircle = [&](const CustomVertex* pVertices, float* pRadius, D3DXVECTOR3* pCenter)
	{
		//! 矩形の辺の長さの半分を円の半径としている
		D3DXVECTOR3 rectSide(pVertices[1].m_pos - pVertices[0].m_pos);
		*pRadius = D3DXVec3Length(&rectSide) * 0.5f;

		//! 矩形の対角線の真ん中は矩形の中心
		*pCenter = pVertices[0].m_pos + (pVertices[2].m_pos - pVertices[0].m_pos) * 0.5f;
	};

	float aRadius = 0.0f;
	D3DXVECTOR3 aCenter;
	FormatRectToCircle(pA, &aRadius, &aCenter);

	float bRadius = 0.0f;
	D3DXVECTOR3 bCenter;
	FormatRectToCircle(pB, &bRadius, &bCenter);

	D3DXVECTOR3 distanceVec = aCenter - bCenter;
	float distance = D3DXVec3Length(&distanceVec);

	if (distance < aRadius + bRadius) return true;

	return false;
}

bool Collision::CollidesRects(const CustomVertex* pA, const CustomVertex* pB) const
{
	//! 片方の矩形の範囲内にもう片方の矩形が一部でも入っているかどうかを判定している
	bool collidesX =
		(pA[0].m_pos.x <= pB[0].m_pos.x && pB[0].m_pos.x <= pA[1].m_pos.x) ||
		(pA[0].m_pos.x <= pB[1].m_pos.x && pB[1].m_pos.x <= pA[1].m_pos.x) ||
		(pB[0].m_pos.x <= pA[0].m_pos.x && pA[1].m_pos.x <= pB[1].m_pos.x);

	bool collidesY =
		(pA[0].m_pos.y <= pB[0].m_pos.y && pB[0].m_pos.y <= pA[3].m_pos.y) ||
		(pA[0].m_pos.y <= pB[3].m_pos.y && pB[3].m_pos.y <= pA[3].m_pos.y) ||
		(pB[0].m_pos.y <= pA[0].m_pos.y && pA[3].m_pos.y <= pB[3].m_pos.y);

	if (collidesX && collidesY) return true;

	return false;
}
