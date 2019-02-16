/// <filename>
/// Behavior.cpp
/// </filename>
/// <summary>
/// パーティクルのふるまいを決めるクラスのソース
/// </summary>

#include "Behavior.h"

#include <Windows.h>
#include <math.h>

# include <random>

#include <d3dx9.h>

#include "IGameLibRenderer\IGameLibRenderer.h"
#include "Algorithm\Algorithm.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

using Algorithm::D3DXVec3RotationZ;
using Algorithm::D3DXVec2RotationZ;

IGameLibRenderer* Behavior::m_pIGameLibRenderer = nullptr;

void Behavior::FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, const D3DXVECTOR2& centerDifference)
{
	std::uniform_real_distribution<float> centerXRand(-centerDifference.x, centerDifference.x);
	std::uniform_real_distribution<float> centerYRand(-centerDifference.y, centerDifference.y);

	pVerticesParam->m_center = m_originCenter = center;
	pVerticesParam->m_center.x += centerXRand(m_randEngine);
	pVerticesParam->m_center.y += centerYRand(m_randEngine);
}

void Behavior::FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float centerDifference)
{
	std::uniform_real_distribution<float> centerRand(0.0f, centerDifference);
	std::uniform_real_distribution<float> radRand(0.0f, 2.0f * D3DX_PI);

	//! 作成するベクトルをランダムに回転させてそれを位置にする
	D3DXVECTOR3 centerDifferenceVec = { centerRand(m_randEngine), 0.0f, pVerticesParam->m_center.z };
	D3DXVec3RotationZ(&centerDifferenceVec, radRand(m_randEngine));

	//! 上で作ったベクトル分中心からずらす
	pVerticesParam->m_center = m_originCenter = center;
	pVerticesParam->m_center += centerDifferenceVec;
}

void Behavior::FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float minLengthToCenter, float centerDifference)
{
	std::uniform_real_distribution<float> centerRand(minLengthToCenter, minLengthToCenter + centerDifference);
	std::uniform_real_distribution<float> radRand(0.0f, 2.0f * D3DX_PI);

	//! 作成するベクトルをランダムに回転させてそれを位置にする
	D3DXVECTOR3 centerDifferenceVec = { centerRand(m_randEngine), 0.0f, pVerticesParam->m_center.z };
	D3DXVec3RotationZ(&centerDifferenceVec, radRand(m_randEngine));

	//! 上で作ったベクトル分中心からずらす
	pVerticesParam->m_center = m_originCenter = center;
	pVerticesParam->m_center += centerDifferenceVec;
}

void Behavior::FormatInitialVelocity(float initialSpeed, float direction_deg, float directionDifference_deg)
{
	std::uniform_real_distribution<float> degRand(-directionDifference_deg, directionDifference_deg);

	D3DXVECTOR2 initialSpeedForRotate = { initialSpeed, 0.0f };
	D3DXVec2RotationZ(&initialSpeedForRotate, D3DXToRadian(direction_deg + degRand(m_randEngine)));
	m_velocity = initialSpeedForRotate;
}

void Behavior::FormatRadiationInitialVelocity(const VerticesParam& VerticesParam, float initialSpeed, float directionDifference_deg)
{
	D3DXVECTOR3 originToCurrentPosVec;
	Algorithm::D3DXVec3Unit(&originToCurrentPosVec, m_originCenter, VerticesParam.m_center);

	FormatInitialVelocity(initialSpeed, Algorithm::CalcDegreeAgainstRightVector(originToCurrentPosVec), directionDifference_deg);
}

void Behavior::FormatAbsorptionInitialVelocity(const VerticesParam& VerticesParam, float initialSpeed, float directionDifference_deg)
{
	D3DXVECTOR3 originToCurrentPosVec;
	Algorithm::D3DXVec3Unit(&originToCurrentPosVec, VerticesParam.m_center, m_originCenter);

	FormatInitialVelocity(initialSpeed, Algorithm::CalcDegreeAgainstRightVector(originToCurrentPosVec), directionDifference_deg);
}

void Behavior::Accelarate(float speed, D3DXVECTOR2 directionVector)
{
	D3DXVECTOR2 unitDirectionVector;
	D3DXVec2Normalize(&unitDirectionVector, &directionVector);

	D3DXVECTOR2 velocity = speed * unitDirectionVector;
	m_velocity += velocity;
}

void Behavior::Accelarate(D3DXVECTOR2 velocity)
{
	m_velocity += velocity;
}

void Behavior::ZeroVelocity()
{
	ZeroMemory(&m_velocity, sizeof(D3DXVECTOR2));
}

void Behavior::CalcCenter(VerticesParam* pVerticesParam)
{
	pVerticesParam->m_center.x += m_velocity.x;
	pVerticesParam->m_center.y += m_velocity.y;
}

void Behavior::CirculationZ(VerticesParam* pVerticesParam, const D3DXVECTOR3& rotationBasePos, float rotationDegMin, float differenceAdditionalRotationDeg)
{
	std::uniform_real_distribution<float> degRand(rotationDegMin, rotationDegMin + differenceAdditionalRotationDeg);

	Algorithm::D3DXVec3CirculationZ(&pVerticesParam->m_center, rotationBasePos, D3DXToRadian(degRand(m_randEngine)));
}

void Behavior::CirculationZ(VerticesParam* pVerticesParam, float rotationDegMin, float differenceAdditionalRotationDeg)
{
	std::uniform_real_distribution<float> degRand(rotationDegMin, rotationDegMin + differenceAdditionalRotationDeg);

	Algorithm::D3DXVec3CirculationZ(&pVerticesParam->m_center, m_originCenter, D3DXToRadian(degRand(m_randEngine)));
}

bool Behavior::IsOutSide(const VerticesParam& verticesParam, const D3DXVECTOR3& additionalRangeMin, float differenceRangeMulti)
{
	std::uniform_real_distribution<float> additionalRangMultiRand(min(1.0f, differenceRangeMulti), max(1.0f, differenceRangeMulti));

	float additionalRangeMulti = additionalRangMultiRand(m_randEngine);
	D3DXVECTOR3 additonalRange =
	{
		additionalRangeMulti * additionalRangeMin.x,
		additionalRangeMulti * additionalRangeMin.y,
		verticesParam.m_center.z
	};

	D3DXVECTOR3 radiusVec = verticesParam.m_center - m_originCenter;
	float radius = D3DXVec3Length(&radiusVec);

	if (radius > D3DXVec3Length(&additonalRange)) return true;

	return false;
}

void Behavior::FadeIn(VerticesParam* pVerticesParam, int startFrame, int takesFrame, int lifeTime) const
{
	if (lifeTime < startFrame || lifeTime > startFrame + takesFrame) return;

	m_pIGameLibRenderer->SetRectAlpha(pVerticesParam, static_cast<BYTE>(255.0f * (lifeTime - startFrame) / takesFrame));
}

void Behavior::FadeOut(VerticesParam* pVerticesParam, int startFrame, int takesFrame, int lifeTime) const
{
	if (lifeTime < startFrame || lifeTime > startFrame + takesFrame) return;

	m_pIGameLibRenderer->SetRectAlpha(pVerticesParam, static_cast<BYTE>(255.0f * (1.0f - (lifeTime - startFrame) / static_cast<float>(takesFrame))));
}
