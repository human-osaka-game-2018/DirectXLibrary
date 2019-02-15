/// <filename>
/// Shape.cpp
/// </filename>
/// <summary>
/// 形状を作成するクラスのソース
/// </summary>

#include "Shape.h"

#include <Windows.h>

# include <random>

#include <d3dx9.h>

#include "GameLib.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

void Shape::Format(VerticesParam* pVerticesParam, float baseScale, float scaleDifferenceMulti)
{
	std::uniform_real_distribution<float> scaleMultiRand(min(1.0f, scaleDifferenceMulti), max(1.0f, scaleDifferenceMulti));

	float scaleMulti = scaleMultiRand(m_randEngine);

	pVerticesParam->m_halfScale = { baseScale * scaleMulti, baseScale * scaleMulti, 0.0f };
}

void Shape::Format(VerticesParam* pVerticesParam, float baseScale, const D3DXVECTOR2& scaleDifferenceMulti)
{
	std::uniform_real_distribution<float> scaleXMultiRand(min(1.0f, scaleDifferenceMulti.x), max(1.0f, scaleDifferenceMulti.x));
	std::uniform_real_distribution<float> scaleYMultiRand(min(1.0f, scaleDifferenceMulti.y), max(1.0f, scaleDifferenceMulti.y));

	pVerticesParam->m_halfScale =
	{
		baseScale * scaleXMultiRand(m_randEngine),
		baseScale * scaleYMultiRand(m_randEngine),
		0.0f
	};
}

void Shape::Format(VerticesParam* pVerticesParam, const D3DXVECTOR2& baseScale, float scaleDifferenceMulti)
{
	std::uniform_real_distribution<float> scaleMultiRand(min(1.0f, scaleDifferenceMulti), max(1.0f, scaleDifferenceMulti));

	float scaleMulti = baseScale.x * scaleMultiRand(m_randEngine);

	pVerticesParam->m_halfScale = { baseScale.x * scaleMulti, baseScale.y * scaleMulti, 0.0f };
}

void Shape::Format(VerticesParam* pVerticesParam, const D3DXVECTOR2& baseScale, const D3DXVECTOR2& scaleDifferenceMulti)
{
	std::uniform_real_distribution<float> scaleXMultiRand(min(1.0f, scaleDifferenceMulti.x), max(1.0f, scaleDifferenceMulti.x));
	std::uniform_real_distribution<float> scaleYMultiRand(min(1.0f, scaleDifferenceMulti.y), max(1.0f, scaleDifferenceMulti.y));

	pVerticesParam->m_halfScale =
	{
		baseScale.x * scaleXMultiRand(m_randEngine),
		baseScale.y * scaleYMultiRand(m_randEngine),
		0.0f
	};
}
