/// <filename>
/// Algorithm.cpp
/// </filename>
/// <summary>
/// 簡易計算をまとめた名前空間のソース
/// </summary>

#include "Algorithm.h"

#include <Windows.h>
#include <math.h>

#include <functional>
# include <random>

#include <d3dx9.h>

void Algorithm::D3DXVec3Unit(D3DXVECTOR3* pOut, const D3DXVECTOR3& origin, const D3DXVECTOR3& dest)
{
	D3DXVECTOR3 distanceVec(dest - origin);
	D3DXVec3Normalize(pOut, &distanceVec);
}

void Algorithm::D3DXVec3CirculationZ(D3DXVECTOR3* pRotationPos, const D3DXVECTOR3& rotationBasePos, float deg)
{
	//! 実質原点に移動したのと同じ
	D3DXVECTOR3 distanceVecToRotationBase(*pRotationPos - rotationBasePos);

	D3DXMATRIX rotationMat;
	D3DXMatrixRotationZ(&rotationMat, D3DXToRadian(deg));

	//! 原点に移動したのを回転
	D3DXVECTOR3 rotationPosOnOrigin;
	D3DXVec3TransformCoord(&rotationPosOnOrigin, &distanceVecToRotationBase, &rotationMat);

	//! 元の位置にずらす
	*pRotationPos = rotationPosOnOrigin + rotationBasePos;
}

void Algorithm::D3DXVec3RotationZ(D3DXVECTOR3* pRotationVec, float deg)
{
	D3DXMATRIX rotateMatrix;
	D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(deg));
	D3DXVec3TransformCoord(pRotationVec, pRotationVec, &rotateMatrix);
}

void Algorithm::D3DXVec2RotationZ(D3DXVECTOR2* pRotationVec, float deg)
{
	D3DXMATRIX rotateMatrix;
	D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(deg));
	D3DXVec2TransformCoord(pRotationVec, pRotationVec, &rotateMatrix);
}

float Algorithm::CalcDegreeAgainstRightVector(const D3DXVECTOR3& vector)
{
	float radian = 0.0f;
	float vectorBaseToCurrentPosLength = D3DXVec3Length(&vector);

	if (vectorBaseToCurrentPosLength != 0.0f)
	{
		const D3DXVECTOR3 BASE_VECTOR = { 1.0f, 0.0f, 0.0f };

		float cos = D3DXVec3Dot(&BASE_VECTOR, &vector) / vectorBaseToCurrentPosLength;
		radian = acos(cos) * ((vector.y >= 0.0f) ? -1.0f : +1.0f);
	}

	return D3DXToDegree(radian);
}

float Algorithm::D3DXVec2Cross(const D3DXVECTOR2& baseVector, const D3DXVECTOR2& vector)
{
	return baseVector.x * vector.y - baseVector.y * vector.x;
}

float Algorithm::D3DXVec3CalcDegree(const D3DXVECTOR3& baseVector, const D3DXVECTOR3& vector)
{
	float radian = 0.0f;

	float vectorsMultiLength = D3DXVec3Length(&baseVector) * D3DXVec3Length(&vector);

	if (vectorsMultiLength != 0.0f)
	{
		float cos = D3DXVec3Dot(&baseVector, &vector) / vectorsMultiLength;
		radian = acos(cos);
	}

	return D3DXToDegree(radian);
}

float Algorithm::D3DXVec2CalcDegree(const D3DXVECTOR2& baseVector, const D3DXVECTOR2& vector)
{
	float radian = 0.0f;

	float vectorsMultiLength = D3DXVec2Length(&baseVector) * D3DXVec2Length(&vector);

	if (vectorsMultiLength != 0.0f)
	{
		float cos = D3DXVec2Dot(&baseVector, &vector) / vectorsMultiLength;
		radian = acos(cos) * ((D3DXVec2Cross(baseVector, vector) >= 0.0f) ? +1.0f : -1.0f);
	}

	return D3DXToDegree(radian);
}

float Algorithm::Lerp(const D3DXVECTOR2& origin, const D3DXVECTOR2& dest, float x)
{
	if (dest.x - origin.x == 0.0f)
	{
		return 0.0f;
	}

	float y = (dest.y - origin.y) * (dest.x - origin.x) / (dest.x - origin.x) + origin.y;

	return y;
}

void Algorithm::CountUp_s(int* pCnt, int cntMax)
{
	++(*pCnt);

	if ((*pCnt) >= cntMax)
	{
		(*pCnt) = 0;
	}
}

void CountUp_s(int* pCnt, int cntMax, std::function<void(void)> pFunc)
{
	++(*pCnt);

	if ((*pCnt) >= cntMax)
	{
		(*pCnt) = 0;
		pFunc();
	}
}
