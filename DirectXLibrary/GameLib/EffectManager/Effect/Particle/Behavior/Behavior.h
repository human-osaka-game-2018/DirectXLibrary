/// <filename>
/// Behavior.h
/// </filename>
/// <summary>
/// パーティクルのふるまいを決めるクラスのヘッダ
/// </summary>

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <Windows.h>
#include <math.h>

# include <random>

#include <d3dx9.h>

#include "Algorithm\Algorithm.h"
#include "GameLib.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

using Algorithm::D3DXVec3RotationZ;
using Algorithm::D3DXVec2RotationZ;

/// <summary>
/// パーティクルのふるまいを決めるクラス
/// </summary>
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

	/// <summary>
	/// 中心の初期化
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="center">基底となる中心</param>
	/// <param name="centerDifference">中心の誤差</param>
	void FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, const D3DXVECTOR2& centerDifference);
	void FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float centerDifference);

	/// <summary>
	/// 中心の初期化
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="center">基底となる中心</param>
	/// <param name="minLengthToCenter">最低どれだけ中心から離れているか</param>
	/// <param name="centerDifference">離れている値の誤差</param>
	void FormatCenter(VerticesParam* pVerticesParam, const D3DXVECTOR3& center, float minLengthToCenter, float centerDifference);

	/// <summary>
	/// 初速度の初期化
	/// </summary>
	/// <param name="initialSpeed">初速度の大きさ</param>
	/// <param name="direction_deg">
	/// 方向の角度(度数法)
	/// ベースはx軸に正の方向
	/// </param>
	/// <param name="directionDifference_deg">方向の角度の誤差</param>
	void FormatInitialVelocity(float initialSpeed, float direction_deg, float directionDifference_deg = 0.0f);

	/// <summary>
	/// 起点に対して放射する初速度の初期化
	/// </summary>
	/// <param name="VerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="initialSpeed">初速度の大きさ</param>
	/// <param name="directionDifference_deg">方向の角度の誤差</param>
	void FormatRadiationInitialVelocity(const VerticesParam& VerticesParam, float initialSpeed, float directionDifference_deg = 0.0f);

	/// <summary>
	/// 起点に対して収束する初速度の初期化
	/// </summary>
	/// <param name="VerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="initialSpeed">初速度の大きさ</param>
	/// <param name="directionDifference_deg">方向の角度の誤差</param>
	void FormatAbsorptionInitialVelocity(const VerticesParam& VerticesParam, float initialSpeed, float directionDifference_deg = 0.0f);

	/*
	* 動作制御関数群 毎フレーム呼ぶ必要がある物もある
	*/

	/// <summary>
	/// 加速させる
	/// </summary>
	/// <param name="speed">速さ</param>
	/// <param name="directionVector">加速させる向き</param>
	void Accelarate(float speed, D3DXVECTOR2 directionVector);

	void Accelarate(D3DXVECTOR2 velocity);

	/// <summary>
	/// 速度を消す
	/// </summary>
	void ZeroVelocity();

	/// <summary>
	/// 速度による中心の再計算
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	void CalcCenter(VerticesParam* pVerticesParam);

	/// <summary>
	/// Z軸で円運動させる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="rotationBasePos">回転の中心</param>
	/// <param name="rotationDegMin">回転の最小角度(度数法)</param>
	/// <param name="differenceAdditionalRotationDeg">追加の回転角度の誤差</param>
	void CirculationZ(VerticesParam* pVerticesParam, const D3DXVECTOR3& rotationBasePos, float rotationDegMin, float differenceAdditionalRotationDeg = 0.0f);

	/// <summary>
	/// 生成時の基底となる中心でZ軸円運動させる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="rotationDegMin">回転の最小角度(度数法)</param>
	/// <param name="differenceAdditionalRotationDeg">追加の回転角度の誤差</param>
	void CirculationZ(VerticesParam* pVerticesParam, float rotationDegMin, float differenceAdditionalRotationDeg = 0.0f);

	/// <summary>
	/// 基底の中心から引数に渡した範囲の外に存在しているか判別し結果を返す
	/// </summary>
	/// <param name="verticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="additionalRangeMin">基底の中心からの最小の範囲</param>
	/// <param name="differenceRangeMulti">
	/// 範囲の誤差の倍率
	/// 2.0fだと最小の範囲から二倍の間で範囲内たと判別される
	/// </param>
	/// <returns>範囲外だとtrue</returns>
	bool IsOutSide(const VerticesParam& verticesParam, const D3DXVECTOR3& additionalRangeMin, float differenceRangeMulti = 1.0f);

	/// <summary>
	/// フェードインさせる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="startFrame">開始するフレーム</param>
	/// <param name="takesFrame">フェードインにかかるフレーム</param>
	/// <param name="lifeTime">現在の生存時間</param>
	void FadeIn(VerticesParam* pVerticesParam, int startFrame, int takesFrame, int lifeTime) const;

	/// <summary>
	/// フェードアウトさせる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="startFrame">開始するフレーム</param>
	/// <param name="takesFrame">フェードアウトにかかるフレーム</param>
	/// <param name="lifeTime">現在の生存時間</param>
	void FadeOut(VerticesParam* pVerticesParam, int startFrame, int takesFrame, int lifeTime) const;

private:
	std::minstd_rand m_randEngine;

	D3DXVECTOR2 m_velocity = { 0.0f, 0.0f };

	D3DXVECTOR3 m_originCenter = { 0.0f, 0.0f, 0.0f };
};

#endif //! BEHAVIOR_H
