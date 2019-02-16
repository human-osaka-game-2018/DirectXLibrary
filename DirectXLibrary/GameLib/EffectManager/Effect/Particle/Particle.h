/// <filename>
/// Particle.h
/// </filename>
/// <summary>
/// パーティクルクラスのヘッダ
/// </summary>

#ifndef PARTICLE_H
#define PARTICLE_H

#include <Windows.h>

#include <d3dx9.h>

#include "Shape/Shape.h"
#include "Behavior/Behavior.h"
#include "IGameLibRenderer\IGameLibRenderer.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

/// <summary>
/// パーティクルクラス
/// </summary>
class Particle
{
public:
	Particle(const TCHAR* pTexPath) :m_pTexName(pTexPath)
	{
		m_pIGameLibRenderer->CreateTex(m_pTexName, m_pTexName);
	}

	virtual ~Particle() {};

	/// <summary>
	/// Effectで入れる
	/// GameLibの描画関係を集めたもの
	/// </summary>
	/// <param name="pIGameLibRenderer">GameLibの描画関連のインターフェイス</param>
	inline void SetGameLibRenderer(IGameLibRenderer* pIGameLibRenderer)
	{
		m_pIGameLibRenderer = pIGameLibRenderer;

		m_behavior.SetGameLibRenderer(pIGameLibRenderer);
	}

	/// <summary>
	/// 形状を誤差ありで作成する
	/// </summary>
	/// <param name="pVerticesParam">[out]矩形作成するためのデータ</param>
	/// <param name="baseScale">基本となる幅</param>
	/// <param name="scaleDifferenceMulti">
	/// 幅に掛け合わされる倍率
	/// ランダムで1.0f~からこの値が掛け合わされる
	/// </param>
	inline void FormatShape(float baseScale, float scaleDifferenceMulti = 1.0f)
	{
		m_shape.Format(&m_verticesParam, baseScale, scaleDifferenceMulti);
	}

	inline void FormatShape(float baseScale, const D3DXVECTOR2& scaleDifferenceMulti)
	{
		m_shape.Format(&m_verticesParam, baseScale, scaleDifferenceMulti);
	}

	inline void FormatShape(const D3DXVECTOR2& baseScale, float scaleDifferenceMulti = 1.0f)
	{
		m_shape.Format(&m_verticesParam, baseScale, scaleDifferenceMulti);
	}

	inline void FormatShape(const D3DXVECTOR2& baseScale, const D3DXVECTOR2& scaleDifferenceMulti)
	{
		m_shape.Format(&m_verticesParam, baseScale, scaleDifferenceMulti);
	}

	/*
	* 初期化関数群 初めに1度しか呼んではいけない
	*/

	/// <summary>
	/// 中心の初期化
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="center">基底となる中心</param>
	/// <param name="centerDifference">中心の誤差</param>
	inline void FormatCenter(const D3DXVECTOR3& center, const D3DXVECTOR2& centerDifference)
	{
		m_behavior.FormatCenter(&m_verticesParam, center, centerDifference);
	}

	inline void FormatCenter(const D3DXVECTOR3& center, float centerDifference)
	{
		m_behavior.FormatCenter(&m_verticesParam, center, centerDifference);
	}

	/// <summary>
	/// 中心の初期化
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="center">基底となる中心</param>
	/// <param name="minLengthToCenter">最低どれだけ中心から離れているか</param>
	/// <param name="centerDifference">離れている値の誤差</param>
	inline void FormatCenter(const D3DXVECTOR3& center, float minLengthToCenter, float centerDifference)
	{
		m_behavior.FormatCenter(&m_verticesParam, center, minLengthToCenter, centerDifference);
	}

	/// <summary>
	/// 初速度の初期化
	/// </summary>
	/// <param name="initialSpeed">初速度の大きさ</param>
	/// <param name="direction_deg">
	/// 方向の角度(度数法)
	/// ベースはx軸に正の方向
	/// </param>
	/// <param name="directionDifference_deg">方向の角度の誤差</param>
	inline void FormatInitialVelocity(float initialSpeed, float direction_deg, float directionDifference_deg = 0.0f)
	{
		m_behavior.FormatInitialVelocity(initialSpeed, direction_deg, directionDifference_deg);
	}

	/// <summary>
	/// 起点に対して放射する初速度の初期化
	/// </summary>
	/// <param name="VerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="initialSpeed">初速度の大きさ</param>
	/// <param name="directionDifference_deg">方向の角度の誤差</param>
	inline void FormatRadiationInitialVelocity(float initialSpeed, float directionDifference_deg = 0.0f)
	{
		m_behavior.FormatRadiationInitialVelocity(m_verticesParam, initialSpeed, directionDifference_deg);
	}

	/// <summary>
	/// 起点に対して収束する初速度の初期化
	/// </summary>
	/// <param name="VerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="initialSpeed">初速度の大きさ</param>
	/// <param name="directionDifference_deg">方向の角度の誤差</param>
	inline void FormatAbsorptionInitialVelocity(float initialSpeed, float directionDifference_deg = 0.0f)
	{
		m_behavior.FormatAbsorptionInitialVelocity(m_verticesParam, initialSpeed, directionDifference_deg);
	}

	/*
	* 動作制御関数群 毎フレーム呼ぶ必要がある物もある
	*/

	/// <summary>
	/// 加速させる
	/// </summary>
	/// <param name="speed">速さ</param>
	/// <param name="directionVector">加速させる向き</param>
	inline void Accelarate(float speed, D3DXVECTOR2 directionVector)
	{
		m_behavior.Accelarate(speed, directionVector);
	}

	inline void Accelarate(D3DXVECTOR2 velocity)
	{
		m_behavior.Accelarate(velocity);
	}

	/// <summary>
	/// 速度を消す
	/// </summary>
	inline void ZeroVelocity()
	{
		m_behavior.ZeroVelocity();
	}

	/// <summary>
	/// 速度による中心の再計算
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	inline void CalcCenter()
	{
		m_behavior.CalcCenter(&m_verticesParam);
	}

	/// <summary>
	/// Z軸で円運動させる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="rotationBasePos">回転の中心</param>
	/// <param name="rotationDegMin">回転の最小角度(度数法)</param>
	/// <param name="differenceAdditionalRotationDeg">追加の回転角度の誤差</param>
	inline void CirculationZ(const D3DXVECTOR3& rotationBasePos, float rotationDegMin, float differenceAdditionalRotationDeg = 0.0f)
	{
		m_behavior.CirculationZ(&m_verticesParam, rotationBasePos, rotationDegMin, differenceAdditionalRotationDeg);
	}

	/// <summary>
	/// 生成時の基底となる中心でZ軸円運動させる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="rotationDegMin">回転の最小角度(度数法)</param>
	/// <param name="differenceAdditionalRotationDeg">追加の回転角度の誤差</param>
	inline void CirculationZ(float rotationDegMin, float differenceAdditionalRotationDeg = 0.0f)
	{
		m_behavior.CirculationZ(&m_verticesParam, rotationDegMin, differenceAdditionalRotationDeg);
	}

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
	inline bool IsOutSide(const D3DXVECTOR3& additionalRangeMin, float differenceRangeMulti = 1.0f)
	{
		m_behavior.IsOutSide(m_verticesParam, additionalRangeMin, differenceRangeMulti);
	}

	/// <summary>
	/// フェードインさせる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="startFrame">開始するフレーム</param>
	/// <param name="takesFrame">フェードインにかかるフレーム</param>
	inline void FadeIn(int startFrame, int takesFrame)
	{
		m_behavior.FadeIn(&m_verticesParam, startFrame, takesFrame, m_lifeFrame);
	}

	/// <summary>
	/// フェードアウトさせる
	/// </summary>
	/// <param name="pVerticesParam">頂点情報を作成するためのデータ</param>
	/// <param name="startFrame">開始するフレーム</param>
	/// <param name="takesFrame">フェードアウトにかかるフレーム</param>
	inline void FadeOut(int startFrame, int takesFrame)
	{
		m_behavior.FadeOut(&m_verticesParam, startFrame, takesFrame, m_lifeFrame);
	}

	/// <summary>
	/// 色を変える
	/// </summary>
	/// <param name="aRGB">変えたいカラーコード</param>
	inline void SetColor(DWORD aRGB)
	{
		m_verticesParam.m_aRGB = aRGB;
	}

	/// <summary>
	/// X軸で回転させる
	/// </summary>
	/// <param name="deg">回転角度(度数法)</param>
	inline void RotateX(float deg)
	{
		m_verticesParam.m_deg.x += deg;
	}

	inline void RotateY(float deg)
	{
		m_verticesParam.m_deg.y += deg;
	}

	inline void RotateZ(float deg)
	{
		m_verticesParam.m_deg.z += deg;
	}

	/// <summary>
	/// 生存時間の初期化
	/// </summary>
	inline void ZeroLifeFrame()
	{
		m_lifeFrame = 0;
	}

	/// <summary>
	/// 生存時間の取得
	/// </summary>
	/// <returns>生存時間</returns>
	inline int GetLifeFrame() const
	{
		return m_lifeFrame;
	}

	/// <summary>
	/// 生存時間を増やし,位置の再計算を行う
	/// </summary>
	virtual inline void Update()
	{
		++m_lifeFrame;

		m_behavior.CalcCenter(&m_verticesParam);
	}

	/// <summary>
	/// 描画を行う
	/// </summary>
	virtual inline void Render()
	{
		m_pIGameLibRenderer->Render(m_verticesParam, m_pIGameLibRenderer->GetTex(m_pTexName));
	}

protected:
	static IGameLibRenderer* m_pIGameLibRenderer;

	VerticesParam m_verticesParam;

	Behavior m_behavior;
	Shape m_shape;

	//! 生存時間(frame)これを用いて動作のタイミングなどを決める
	int m_lifeFrame = 0;

	const TCHAR* m_pTexName = nullptr;
};

#endif //! PARTICLE_H
