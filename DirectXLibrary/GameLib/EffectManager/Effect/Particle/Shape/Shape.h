/// <filename>
/// Shape.h
/// </filename>
/// <summary>
/// 形状を作成するクラスのヘッダ
/// </summary>

#ifndef SHAPE_H
#define SHAPE_H

#include <Windows.h>

# include <random>

#include <d3dx9.h>

#include "VerticesParam.h"
#include "CustomVertex.h"

/// <summary>
/// 形状を細かく調整することができるクラス
/// </summary>
class Shape
{
public:
	Shape() 
	{
		//! random_deviceだけでも乱数は作れるが処理が重いのでシードとして扱う
		std::random_device randDevForSeed;
		m_randEngine.seed(randDevForSeed());
	}

	~Shape() {};

	/// <summary>
	/// 形状を誤差ありで作成する
	/// </summary>
	/// <param name="pVerticesParam">[out]矩形作成するためのデータ</param>
	/// <param name="baseScale">基本となる幅</param>
	/// <param name="scaleDifferenceMulti">
	/// 幅に掛け合わされる倍率
	/// ランダムで1.0f~からこの値が掛け合わされる
	/// </param>
	void Format(VerticesParam* pVerticesParam, float baseScale, float scaleDifferenceMulti = 1.0f);
	void Format(VerticesParam* pVerticesParam, float baseScale, const D3DXVECTOR2& scaleDifferenceMulti);
	void Format(VerticesParam* pVerticesParam, const D3DXVECTOR2& baseScale, float scaleDifferenceMulti = 1.0f);
	void Format(VerticesParam* pVerticesParam, const D3DXVECTOR2& baseScale, const D3DXVECTOR2& scaleDifferenceMulti);

protected:
	std::minstd_rand m_randEngine;
};

#endif //! SHAPE_H
