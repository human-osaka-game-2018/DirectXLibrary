/// <filename>
/// 
/// </filename>
/// <summary>
/// 
/// </summary>
/// <author>
/// 
/// </author>

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <Windows.h>
#include <math.h>

# include <random>

#include <d3dx9.h>

#include "GameLib.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

class Behavior
{
public:
	Behavior() 
	{
		std::random_device randDevForSeed;
		m_randEngine.seed(randDevForSeed());
	}

	~Behavior() {};

	/*
	* 初期化関数群 初めに1度しか呼んではいけない
	*/
	//inline VOID FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float centerDifferenceX, float centerDifferenceY)
	//{
	//	std::uniform_real_distribution<float> centerXRand(-centerDifferenceX, centerDifferenceX);
	//	std::uniform_real_distribution<float> centerYRand(-centerDifferenceY, centerDifferenceY);
	//	
	//	pVerticesParam->m_center = m_baseCenter = center;
	//	pVerticesParam->m_center.x += centerXRand(m_randEngine);
	//	pVerticesParam->m_center.y += centerYRand(m_randEngine);
	//}

	inline VOID FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float centerDifference)
	{
		std::uniform_real_distribution<float> centerRand(-centerDifference, centerDifference);
		std::uniform_real_distribution<float> radRand(0.0f, 2.0f * D3DX_PI);

		D3DXVECTOR3 centerDifferenceVec = { centerRand(m_randEngine), 0.0f, pVerticesParam->m_center.z };

		RotateVec3(&centerDifferenceVec, radRand(m_randEngine));

		pVerticesParam->m_center = m_baseCenter = center;
		pVerticesParam->m_center += centerDifferenceVec;
	}

	inline VOID FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float minLengthToCenter, float centerDifference)
	{
		std::uniform_real_distribution<float> centerRand(minLengthToCenter, minLengthToCenter + centerDifference);
		std::uniform_real_distribution<float> radRand(0.0f, 2.0f * D3DX_PI);

		D3DXVECTOR3 centerDifferenceVec = { centerRand(m_randEngine), 0.0f, pVerticesParam->m_center.z };

		RotateVec3(&centerDifferenceVec, radRand(m_randEngine));

		pVerticesParam->m_center = m_baseCenter = center;
		pVerticesParam->m_center += centerDifferenceVec;
	}

	inline VOID FormatInitialVelocity(float initialSpeed, float direction_deg, float directionDifference_deg = 0.0f)
	{
		std::uniform_real_distribution<float> degRand(-directionDifference_deg, directionDifference_deg);

		D3DXMATRIX rotateMatrix;
		D3DXVECTOR2 initialSpeedForRotate = { initialSpeed, 0.0f };
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(direction_deg + degRand(m_randEngine)));
		D3DXVec2TransformCoord(&m_velocity, &initialSpeedForRotate, &rotateMatrix);
	}

	inline VOID FormatRadiationInitialVelocity(const VerticesParam& VerticesParam, float initialSpeed, float directionDifference_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = VerticesParam.m_center;
		vectorBaseToCurrentPos -= m_baseCenter;

		FormatInitialVelocity(initialSpeed, CalcDegreeAgainstRightVector(vectorBaseToCurrentPos), directionDifference_deg);
	}

	inline VOID FormatAbsorptionInitialVelocity(const VerticesParam& VerticesParam, float initialSpeed, float directionDifference_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = m_baseCenter;
		vectorBaseToCurrentPos -= VerticesParam.m_center;

		FormatInitialVelocity(initialSpeed, CalcDegreeAgainstRightVector(vectorBaseToCurrentPos), directionDifference_deg);
	}

	/*
	* 動作制御関数群 毎フレーム呼ぶ必要がある物もある
	*/
	inline VOID Accelarate(float speed, D3DXVECTOR2 directionVector)
	{
		D3DXVECTOR2 unitDirectionVector;
		D3DXVec2Normalize(&unitDirectionVector, &directionVector);

		D3DXVECTOR2 velocity = speed * unitDirectionVector;
		m_velocity += velocity;
	}

	inline VOID Accelarate(D3DXVECTOR2 velocity)
	{
		m_velocity += velocity;
	}

	inline VOID ZeroVelocity()
	{
		ZeroMemory(&m_velocity, sizeof(D3DXVECTOR2));
	}

	inline VOID CalcCenter(VerticesParam* pVerticesParam)
	{
		pVerticesParam->m_center.x += m_velocity.x;
		pVerticesParam->m_center.y += m_velocity.y;
	}

	inline VOID Circulate(VerticesParam* pVerticesParam, const D3DXVECTOR3& rotationBasePos, float minRotate_deg, float differenceAdditionalRotate_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = pVerticesParam->m_center - rotationBasePos;

		std::uniform_real_distribution<float> degRand(minRotate_deg, minRotate_deg + differenceAdditionalRotate_deg);

		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(degRand(m_randEngine)));
		D3DXVec3TransformCoord(&vectorBaseToCurrentPos, &vectorBaseToCurrentPos, &rotateMatrix);
		
		pVerticesParam->m_center = vectorBaseToCurrentPos + rotationBasePos;
	}

	inline VOID Circulate(VerticesParam* pVerticesParam, float minRotate_deg, float differenceAdditionalRotate_deg = 0.0f)
	{
		D3DXVECTOR3 vectorBaseToCurrentPos = pVerticesParam->m_center - m_baseCenter;

		std::uniform_real_distribution<float> degRand(minRotate_deg, minRotate_deg + differenceAdditionalRotate_deg);

		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, -D3DXToRadian(degRand(m_randEngine)));
		D3DXVec3TransformCoord(&vectorBaseToCurrentPos, &vectorBaseToCurrentPos, &rotateMatrix);

		pVerticesParam->m_center = vectorBaseToCurrentPos + m_baseCenter;
	}

	/*
	* 処理をループさせるための関数
	*/
	inline bool IsOutSide(const VerticesParam& objData, const D3DXVECTOR3& additionalRangeMin, float differenceAdditionalRangeMulti = 0.0f)
	{
		std::uniform_real_distribution<float> additionalRangMultiRand(1.0f, 1.0f + differenceAdditionalRangeMulti);

		float additionalRangMulti  = additionalRangMultiRand(m_randEngine);
		D3DXVECTOR3 additonalRange = { additionalRangMulti * additionalRangeMin.x, additionalRangMulti * additionalRangeMin.y, objData.m_center.z };

		D3DXVECTOR3 radiusVec = objData.m_center - m_baseCenter;
		float radius = D3DXVec3Length(&radiusVec);

		if (radius > D3DXVec3Length(&additonalRange)) return true;

		return false;
	}

	inline VOID SetAlpha(VerticesParam* pVerticesParam , BYTE alpha)
	{
		pVerticesParam->m_aRGB &= 0x00FFFFFF;
		pVerticesParam->m_aRGB += (alpha << 24);
	}

	inline VOID FadeIn(VerticesParam* pVerticesParam, int startFrame, int takesFrame, int lifeTime)
	{
		if (lifeTime < startFrame || lifeTime > startFrame + takesFrame) return;

		SetAlpha(pVerticesParam, static_cast<BYTE>(255.0f * (lifeTime - startFrame) / takesFrame));
	}

	inline VOID FadeOut(VerticesParam* pVerticesParam, int startFrame, int takesFrame, int lifeTime)
	{
		if (lifeTime < startFrame || lifeTime > startFrame + takesFrame) return;

		SetAlpha(pVerticesParam, static_cast<BYTE>(255.0f * (1.0f - (lifeTime - startFrame) / static_cast<float>(takesFrame))));
	}

private:
	inline float CalcDegreeAgainstRightVector(const D3DXVECTOR3& vectorPos) const
	{
		float radian = 0.0f;
		float vectorBaseToCurrentPosLength = D3DXVec3Length(&vectorPos);

		if (vectorBaseToCurrentPosLength != 0.0f)
		{
			const D3DXVECTOR3 BASE_VECTOR = { 1.0f, 0.0f, m_baseCenter.z };

			float cos = D3DXVec3Dot(&BASE_VECTOR, &vectorPos) / vectorBaseToCurrentPosLength;
			radian = acos(cos) * ((vectorPos.y >= 0.0f) ? -1.0f : +1.0f);
		}

		return D3DXToDegree(radian);
	}

	inline VOID RotateVec3(D3DXVECTOR3* pVec3, float rad)
	{
		D3DXMATRIX rotateMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, rad);
		D3DXVec3TransformCoord(pVec3, pVec3, &rotateMatrix);
	}

	std::minstd_rand m_randEngine;

	D3DXVECTOR2 m_velocity = { 0.0f, 0.0f };

	D3DXVECTOR3 m_baseCenter = { 0.0f, 0.0f, 0.0f };
};

#endif //! BEHAVIOR_H
