#ifndef PARTICLE_H
#define PARTICLE_H

#include <Windows.h>

#include <d3dx9.h>

#include "VerticesParam.h"
#include "CustomVertex.h"
#include "Behavior/Behavior.h"
#include "Shape/Shape.h"

class Particle
{
public:
	Particle(const TCHAR* pTexPath) :m_pTexName(pTexPath)
	{
		m_rGameLib.CreateTex(m_pTexName, m_pTexName);
	}

	virtual ~Particle() {};

	/*
	* 初期化関数群 初めに1度しか呼んではいけない
	*/
	inline VOID FormatShape(const D3DXVECTOR2& minScale, float additionalScaleDifferenceMulti = 0.0f)
	{
		m_shape.Format(&m_objData, minScale, additionalScaleDifferenceMulti);
	}

	//inline VOID FormatCenter(const D3DXVECTOR3& center, float centerDifferenceX, float centerDifferenceY)
	//{
	//	m_behavior.FormatCenter(&m_objData, center, centerDifferenceX, centerDifferenceY);
	//}

	inline VOID FormatCenter(const D3DXVECTOR3& center, float centerDifference)
	{
		m_behavior.FormatCenter(&m_objData, center, centerDifference);
	}

	inline VOID FormatCenter(const D3DXVECTOR3& center, float minLengthToCenter, float centerDifference)
	{
		m_behavior.FormatCenter(&m_objData, center, minLengthToCenter, centerDifference);
	}

	inline VOID FormatInitialVelocity(float initialSpeed, float direction_deg, float directionDifference_deg = 0.0f)
	{
		m_behavior.FormatInitialVelocity(initialSpeed, direction_deg, directionDifference_deg);
	}

	inline VOID FormatRadiationInitialVelocity(float initialSpeed, float directionDifference_deg = 0.0f)
	{
		m_behavior.FormatRadiationInitialVelocity(m_objData, initialSpeed, directionDifference_deg);
	}

	inline VOID FormatAbsorptionInitialVelocity(float initialSpeed, float directionDifference_deg = 0.0f)
	{
		m_behavior.FormatAbsorptionInitialVelocity(m_objData, initialSpeed, directionDifference_deg);
	}

	/*
	* 動作制御関数群 毎フレーム呼ぶ必要がある物もある
	*/
	inline VOID Accelarate(float speed, D3DXVECTOR2 directionVector)
	{
		m_behavior.Accelarate(speed, directionVector);
	}

	inline VOID Accelarate(D3DXVECTOR2 velocity)
	{
		m_behavior.Accelarate(velocity);
	}

	inline VOID ZeroVelocity()
	{
		m_behavior.ZeroVelocity();
	}

	inline VOID Circulate(const D3DXVECTOR3& rotationBasePos, float minRotate_deg, float differenceAdditionalRotate_deg = 0.0f)
	{
		m_behavior.Circulate(&m_objData, rotationBasePos, minRotate_deg, differenceAdditionalRotate_deg);
	}

	inline VOID Circulate(float minRotate_deg, float differenceAdditionalRotate_deg = 0.0f)
	{
		m_behavior.Circulate(&m_objData, minRotate_deg, differenceAdditionalRotate_deg);
	}

	/*
	* 処理をループさせるための関数
	*/
	inline bool IsOutSide(const D3DXVECTOR3& additionalRangeMin, float differenceAdditionalRangeMulti = 0.0f)
	{
		return m_behavior.IsOutSide(m_objData, additionalRangeMin, differenceAdditionalRangeMulti);
	}

	inline VOID SetColor(DWORD color)
	{
		m_objData.m_aRGB = color;
	}

	inline VOID SetAlpha(BYTE  alpha)
	{
		m_behavior.SetAlpha(&m_objData, alpha);
	}

	inline VOID FadeIn(int startFrame, int takesFrame)
	{
		m_behavior.FadeIn(&m_objData, startFrame, takesFrame, m_lifeFrame);
	}

	inline VOID FadeOut(int startFrame, int takesFrame)
	{
		m_behavior.FadeOut(&m_objData, startFrame, takesFrame, m_lifeFrame);
	}

	inline VOID RotateX(float deg)
	{
		m_objData.m_deg.x += deg;
	}

	inline VOID RotateY(float deg)
	{
		m_objData.m_deg.y += deg;
	}

	inline VOID RotateZ(float deg)
	{
		m_objData.m_deg.z += deg;
	}

	inline VOID ZeroLifeFrame()
	{
		m_lifeFrame = 0;
	}

	inline int LifeFrame() const
	{
		return m_lifeFrame;
	}

	virtual inline VOID Update()
	{
		++m_lifeFrame;

		m_behavior.CalcCenter(&m_objData);
	}

	virtual inline VOID Render()
	{
		CreateAndRenderRect();
	}

protected:
	VOID CreateAndRenderRect()
	{
		CustomVertex customVertex[4];

		m_rGameLib.CreateRect(customVertex, m_objData);
		m_rGameLib.Render(customVertex, m_rGameLib.GetTex(m_pTexName));
	}

	GameLib& m_rGameLib = GameLib::GetInstance();

	VerticesParam m_objData;

	Behavior m_behavior;
	Shape m_shape;

	int m_lifeFrame = 0;

	const TCHAR* m_pTexName = nullptr;
};

#endif //! PARTICLE_H
