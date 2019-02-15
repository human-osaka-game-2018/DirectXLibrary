/// <filename>
/// CustomVerticesEditor.cpp
/// </filename>
/// <summary>
/// 頂点データ構造体の編集を行うクラスのソース
/// </summary>

#include "CustomVertexEditor.h"

#include <Windows.h>

#include <d3dx9.h>

#include "Algorithm\Algorithm.h"
#include "CustomVertex.h"
#include "VerticesParam.h"

void CustomVertexEditor::RotateXYZ(CustomVertex* pCustomVertices, const RotateValueXYZ& deg, const D3DXVECTOR3& relativeRotateCenter) const
{
	RotateX(
		pCustomVertices,
		deg.x,
		relativeRotateCenter);

	RotateY(
		pCustomVertices,
		deg.y,
		relativeRotateCenter);

	RotateZ(pCustomVertices,
		deg.z,
		relativeRotateCenter);
}

void CustomVertexEditor::RotateXYZ(CustomVertex* pCustomVertices, const RotateValueXYZ& deg) const
{
	//! 回転軸が中心からどのくらい離れているかこの関数では離れていない
	D3DXVECTOR3 relativeRotateCenter(0.0f, 0.0f, 0.0f);

	RotateX(
		pCustomVertices,
		deg.x,
		relativeRotateCenter);

	RotateY(
		pCustomVertices,
		deg.y,
		relativeRotateCenter);

	RotateZ(pCustomVertices,
		deg.z,
		relativeRotateCenter);
}

void CustomVertexEditor::RotateX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
{
	if (deg == 0.0f) return;

	D3DXMATRIX rotate;
	D3DXMatrixRotationX(&rotate, D3DXToRadian(deg));
	Rotate(
		pCustomVertices,
		relativeRotateCenter,
		rotate);
}

void CustomVertexEditor::RotateY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
{
	if (deg == 0.0f) return;

	D3DXMATRIX rotate;
	D3DXMatrixRotationY(&rotate, D3DXToRadian(deg));
	Rotate(
		pCustomVertices,
		relativeRotateCenter,
		rotate);
}

void CustomVertexEditor::RotateZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
{
	if (deg == 0.0f) return;

	D3DXMATRIX rotate;
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(deg));
	Rotate(
		pCustomVertices,
		relativeRotateCenter,
		rotate);
}

void CustomVertexEditor::Rotate(CustomVertex* pCustomVertices, 
	const D3DXVECTOR3& relativeRotateCenter, const D3DXMATRIX& rRotate) const
{
	//! 対角線によってすでに回転が行われている矩形の中心も割り出せる
	D3DXVECTOR3 rectCenter((pCustomVertices[0].m_pos + pCustomVertices[2].m_pos) * 0.5f);

	//! 回転の中心は必ずしも矩形の中心ではないので
	D3DXVECTOR3 verticesRectCenterToOrigin[m_RECT_VERTICES_NUM];
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		verticesRectCenterToOrigin[i] = pCustomVertices[i].m_pos - rectCenter;
	};

	//! 回転後元の位置に戻すため
	D3DXVECTOR3 verticesRotateCenterToOrigin[m_RECT_VERTICES_NUM];
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		verticesRotateCenterToOrigin[i] = verticesRectCenterToOrigin[i]- relativeRotateCenter;
	};

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		D3DXVec3TransformCoord(
			&pCustomVertices[i].m_pos,
			&verticesRotateCenterToOrigin[i],
			&rRotate);

		//! 元の位置に戻す
		D3DXVec3Add(
			&pCustomVertices[i].m_pos,
			&pCustomVertices[i].m_pos,
			&rectCenter);

		D3DXVec3Add(
			&pCustomVertices[i].m_pos,
			&pCustomVertices[i].m_pos,
			&relativeRotateCenter);
	}
}

void CustomVertexEditor::Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const
{
	D3DXVECTOR2 rectCenter((pCustomVertices[0].m_pos + pCustomVertices[2].m_pos) * 0.5f);

	D3DXVECTOR2 distancesVertexBetweenCenter[m_RECT_VERTICES_NUM];

	//! 頂点から中心までの長さを求める
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		distancesVertexBetweenCenter[i].x = pCustomVertices[i].m_pos.x - rectCenter.x;
		distancesVertexBetweenCenter[i].y = pCustomVertices[i].m_pos.y - rectCenter.y;
	};

	//! 中心から矩形を再構成させる
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		pCustomVertices[i].m_pos.x = scaleRate.x * distancesVertexBetweenCenter[i].x + rectCenter.x;
		pCustomVertices[i].m_pos.y = scaleRate.y * distancesVertexBetweenCenter[i].y + rectCenter.y;
	}
}

void CustomVertexEditor::Move(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		D3DXVec3Add(
			&pCustomVertices[i].m_pos,
			&pCustomVertices[i].m_pos,
			&movement);
	}
}

void CustomVertexEditor::Locale(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		pCustomVertices[i].m_pos = pos;
	}
}

void CustomVertexEditor::SetTexUV(CustomVertex* pCustomVertices, float startTU, float startTV, float endTU, float endTV) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		pCustomVertices[i].m_texUV.x = (i == 1 || i == 2) ? endTU : startTU;
		pCustomVertices[i].m_texUV.y = (i / 2) ? endTV : startTV;
	}
}

void CustomVertexEditor::SetARGB(CustomVertex *pCustomVertices, DWORD aRGB) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		pCustomVertices[i].m_aRGB = aRGB;
	}
}

void CustomVertexEditor::SetTopBottomARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		if (i < m_RECT_VERTICES_NUM / 2)
		{
			pCustomVertices[i].m_aRGB = topARGB;

			continue;
		}

		pCustomVertices[i].m_aRGB = bottomARGB;
	}
}

void CustomVertexEditor::SetLeftRightARGB(CustomVertex *pCustomVertices, DWORD leftARGB, DWORD rightARGB) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		if (i == 0 || i == 3)
		{
			pCustomVertices[i].m_aRGB = leftARGB;

			continue;
		}

		pCustomVertices[i].m_aRGB = rightARGB;
	}
}

void CustomVertexEditor::Flash(CustomVertex* pVertices, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin) const
{
	BYTE alpha = static_cast<BYTE>(Algorithm::SwitchMinBetweenMax(*pFrameCnt, flashFlameMax, alphaMin, alphaMax));

	SetAlpha(pVertices, alpha);

	Algorithm::CountUp_s(pFrameCnt, flashFlameMax);
}

void CustomVertexEditor::Flash(VerticesParam* pVerticesParam, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin) const
{
	BYTE alpha = static_cast<BYTE>(Algorithm::SwitchMinBetweenMax(*pFrameCnt, flashFlameMax, alphaMin, alphaMax));

	SetAlpha(pVerticesParam, alpha);

	Algorithm::CountUp_s(pFrameCnt, flashFlameMax);
}

	{
		(*pFrameCnt) = 0;
	}
}

void CustomVertexEditor::SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
{
	DWORD aveColor = 0;
	SetAverageARGB(&aveColor, topARGB, bottomARGB);

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		if (i == 0)
		{
			pCustomVertices[i].m_aRGB = topARGB;

			continue;
		}

		if (i == 2)
		{
			pCustomVertices[i].m_aRGB = bottomARGB;

			continue;
		}

		pCustomVertices[i].m_aRGB = aveColor;
	}
}

void CustomVertexEditor::SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
{
	DWORD aveColor = 0;
	SetAverageARGB(&aveColor, topARGB, bottomARGB);

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		if (i == 1)
		{
			pCustomVertices[i].m_aRGB = bottomARGB;

			continue;
		}

		if (i == 3)
		{
			pCustomVertices[i].m_aRGB = topARGB;

			continue;
		}

		pCustomVertices[i].m_aRGB = aveColor;
	}
}

void CustomVertexEditor::Create(CustomVertex* pCustomVertices, const D3DXVECTOR3& center, const D3DXVECTOR3& halfScale,
	DWORD aRGB, float startTU, float startTV, float endTU, float endTV) const
{
	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		pCustomVertices[i].m_pos = center;
		pCustomVertices[i].m_pos.x += (i == 1 || i == 2) ? halfScale.x : -halfScale.x;
		pCustomVertices[i].m_pos.y += (i / 2) ? halfScale.y : -halfScale.y;
		pCustomVertices[i].m_aRGB = aRGB;
	}

	SetTexUV(
		pCustomVertices,
		startTU, startTV,
		endTU, endTV);
}

void CustomVertexEditor::Create(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const
{
	Create(
		pCustomVertices,
		verticesParam.m_center, verticesParam.m_halfScale,
		verticesParam.m_aRGB,
		verticesParam.m_texUV.m_startTU, verticesParam.m_texUV.m_startTV,
		verticesParam.m_texUV.m_endTU, verticesParam.m_texUV.m_endTV);

	RotateXYZ(pCustomVertices, verticesParam.m_deg);
}

void CustomVertexEditor::SetAverageARGB(DWORD* averageARGB, DWORD aARGB, DWORD bARGB) const
{
	BYTE alphaValue[2] = { static_cast<BYTE>(aARGB >> 24) ,static_cast<BYTE>(bARGB >> 24) };
	averageARGB += (((alphaValue[0] + alphaValue[1]) / 2) << 24);

	BYTE redValue[2] = { static_cast<BYTE>(aARGB >> 16) ,static_cast<BYTE>(bARGB >> 16) };
	averageARGB += (((redValue[0] + redValue[1]) / 2) << 16);

	BYTE greenValue[2] = { static_cast<BYTE>(aARGB >> 8) ,static_cast<BYTE>(bARGB >> 8) };
	averageARGB += (((greenValue[0] + greenValue[1]) / 2) << 8);

	BYTE blueValue[2] = { static_cast<BYTE>(aARGB) ,static_cast<BYTE>(bARGB) };
	averageARGB += ((blueValue[0] + blueValue[1]) / 2);
}
