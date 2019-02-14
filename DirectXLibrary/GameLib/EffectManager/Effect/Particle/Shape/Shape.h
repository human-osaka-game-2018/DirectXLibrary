#ifndef SHAPE_H
#define SHAPE_H

#include <Windows.h>

# include <random>

#include <d3dx9.h>

#include "GameLib.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

class Shape
{
public:
	Shape() {};
	~Shape() {};

	inline VOID Format(VerticesParam* pVerticesParam, const D3DXVECTOR2& minScale, float additionalScaleDifferenceMulti = 0.0f) const
	{
		std::random_device randDev;
		std::minstd_rand randEngine(randDev());
		
		float scaleDifferenceMulti = 1.0f + additionalScaleDifferenceMulti;
		std::uniform_real_distribution<float> scaleMultiRand(1.0f, scaleDifferenceMulti);

		float scaleMulti = minScale.x * scaleMultiRand(randEngine);

		pVerticesParam->m_halfScale = { minScale.x * scaleMulti, minScale.y * scaleMulti, 0.0f };
	}
};

#endif //! SHAPE_H
