/// <filename>
/// Algorithm.h
/// </filename>
/// <summary>
/// 簡易計算をまとめた名前空間のヘッダ
/// </summary>

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <Windows.h>
#include <math.h>

#include <functional>
# include <random>

#include <d3dx9.h>

#include "TimerManager\TimerManager.h"

/// <summary>
/// 簡易計算をまとめた名前空間
/// </summary>
namespace Algorithm
{
	/// <summary>
	/// 二点間から単位ベクトルを作成する
	/// </summary>
	/// <param name="pOut">[out]作成したベクトルを入れる</param>
	/// <param name="origin">[in]起点</param>
	/// <param name="dest">[in]行先</param>
	void D3DXVec3Unit(D3DXVECTOR3* pOut, const D3DXVECTOR3& origin, const D3DXVECTOR3& dest);

	/// <summary>
	/// 円運動させる
	/// </summary>
	/// <param name="pRotationPos">円運動させたい点</param>
	/// <param name="rotationBasePos">円運動の中心点</param>
	/// <param name="deg">回転角度(度数法)</param>
	void D3DXVec3CirculationZ(D3DXVECTOR3* pRotationPos, const D3DXVECTOR3& rotationBasePos, float deg);

	/// <summary>
	/// 3次元ベクトルを回転させる
	/// </summary>
	/// <param name="pRotationVec">回転させたいベクトル</param>
	/// <param name="deg">回転角度(度数法)</param>
	void D3DXVec3RotationZ(D3DXVECTOR3* pRotationVec, float deg);

	/// <summary>
	/// 2次元ベクトルを回転させる
	/// </summary>
	/// <param name="pRotationVec">回転させたいベクトル</param>
	/// <param name="deg">回転角度(度数法)</param>
	void D3DXVec2RotationZ(D3DXVECTOR2* pRotationVec, float deg);

	/// <summary>
	/// BASE_VECTOR( 1.0f, 0.0f, 0.0f )
	/// に対してどれほど回転しているかを返す
	/// </summary>
	/// <param name="vector">回転角度を調べたいベクトル</param>
	/// <returns>回転角度(度数法)</returns>
	float CalcDegreeAgainstRightVector(const D3DXVECTOR3& vector);

	/// <summary>
	/// 二次元ベクトルの外積を行う
	/// </summary>
	/// <param name="baseVector">基底となるベクトル</param>
	/// <param name="vector">もう一つのベクトル</param>
	/// <returns>外積結果</returns>
	float D3DXVec2Cross(const D3DXVECTOR2& baseVector, const D3DXVECTOR2& vector);

	/// <summary>
	/// 三次元ベクトル同士の角度を求める
	/// </summary>
	/// <param name="baseVector">基底となるベクトル</param>
	/// <param name="vector">もう一つのベクトル</param>
	/// <returns>角度(度数法)</returns>
	float D3DXVec3CalcDegree(const D3DXVECTOR3& baseVector, const D3DXVECTOR3& vector);
	float D3DXVec2CalcDegree(const D3DXVECTOR2& baseVector, const D3DXVECTOR2& vector);

	/// <summary>
	/// 0~1を行き来する値を引数によって返す
	/// </summary>
	/// <param name="val">現在の進行度の値</param>
	/// <param name="cycleVal">1周期にかかる値</param>
	/// <returns>0~1の値</returns>
	template<typename T>
	float SwitchZeroBetweenOne(T val, T cycleVal)
	{
		float progressRatio = static_cast<float>(val) / static_cast<float>(cycleVal);

		//! cos波を調整し0~1を行き来する値を作成
		return (cos(2.0f * D3DX_PI * progressRatio) + 1.0f) * 0.5f;
	}

	/// <summary>
	/// 引数の値を行き来する値を返す
	/// </summary>
	/// <param name="val">現在の進行度の値</param>
	/// <param name="cycleVal">1周期にかかる値</param>
	/// <param name="switchingMin">行き来する最小値</param>
	/// <param name="switchingMax">行き来する最大値</param>
	/// <returns>引数の値を行き来する値</returns>
	template<typename T1, typename T2>
	float SwitchMinBetweenMax(T1 val, T1 cycleVal, T2 switchingMin, T2 switchingMax)
	{
		return (switchingMax - switchingMin) * SwitchZeroBetweenOne(val, cycleVal) + switchingMin;
	}

	/// <summary>
	/// 線形補間
	/// </summary>
	/// <param name="origin">始点</param>
	/// <param name="dest">終点</param>
	/// <param name="x">補間したいx</param>
	/// <returns>補間されたy</returns>
	float Lerp(const D3DXVECTOR2& origin, const D3DXVECTOR2& dest, float x);

	/// <summary>
	/// カウントアップし最大値に達すると引数の関数を呼び,カウンタを0に戻す
	/// </summary>
	/// <param name="pCnt">[in,out]カウンタのポインタ</param>
	/// <param name="cntMax">カウントの最大値</param>
	/// <param name="pFunc">最大値に達したときに呼ぶ関数のポインタ</param>
	/// <remarks>pFuncがnullptrなら何も呼ばない</remarks>
	void CountUp(int* pCnt, int cntMax, std::function<void(void)> pFunc = nullptr);

	/// <summary>
	/// 一フレームの経過秒を用いてカウントアップし,最大値に達すると引数の関数を呼び,カウンタを0に戻す
	/// </summary>
	/// <param name="pCnt">[in,out]カウンタのポインタ(秒)</param>
	/// <param name="cntMax">カウントの最大値(秒)</param>
	/// <param name="pFunc">最大値に達したときに呼ぶ関数のポインタ</param>
	/// <remarks>pFuncがnullptrなら何も呼ばない</remarks>
	void CountUp_s(float* pCnt_s, float cntMax_s, std::function<void(void)> pFunc = nullptr);
}

#endif //! ALGORITHM_H
