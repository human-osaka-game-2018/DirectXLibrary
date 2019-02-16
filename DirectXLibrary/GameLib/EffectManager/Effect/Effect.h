/// <filename>
/// Effect.h
/// </filename>
/// <summary>
/// エフェクト基底クラスのヘッダ
/// </summary>

#ifndef EFFECT_H
#define EFFECT_H

#include <Windows.h>

#include <d3dx9.h>

#include <vector>

#include "Particle/Particle.h"
#include "Algorithm\Algorithm.h"
#include "IGameLibRenderer\IGameLibRenderer.h"

/// <summary>
/// エフェクト基底クラス
/// </summary>
class Effect
{
public:
	//! activeCountを2にすると2フレームに一つずつパーティクルが増えていく
	Effect(size_t particlesNum, const TCHAR* pTexPath, int activeCount) :m_COUNT_TO_ACTIVE_MAX(activeCount)
	{
		m_particles.resize(particlesNum);

		for (auto& i : m_particles)
		{
			i = new Particle(pTexPath);
		}
	}

	virtual ~Effect() 
	{
		for (auto i : m_particles)
		{
			delete i;
		}

		m_particles.clear();
		m_particles.shrink_to_fit();
	}

	/// <summary>
	/// EffectManagerで入れる
	/// GameLibの描画関係を集めたもの
	/// </summary>
	/// <param name="pIGameLibRenderer">GameLibの描画関連のインターフェイス</param>
	inline void SetGameLibRenderer(IGameLibRenderer* pIGameLibRenderer)
	{
		m_pIGameLibRenderer = pIGameLibRenderer;

		for (auto i : m_particles)
		{
			i->SetGameLibRenderer(pIGameLibRenderer);
		}
	}

	virtual inline void Update() = 0;

	/// <summary>
	/// パーティクルの描画
	/// </summary>
	void Render();

	/// <summary>
	/// エフェクトが終了しているかどうか
	/// </summary>
	/// <returns>終了していればtrue</returns>
	inline bool GetEnds() const
	{
		return m_ends;
	}

protected:
	/// <summary>
	/// カウントをとりパーティクルをアクティブ状態にする
	/// </summary>
	void CountUpActiveLimit();

	/// <summary>
	/// アクティブになっているパーティクルを初期化する
	/// </summary>
	void InitActivatedParticle();

	virtual void Init(Particle* pParticle) = 0;

	IGameLibRenderer* m_pIGameLibRenderer = nullptr;

	std::vector<Particle*> m_particles;

	const int m_COUNT_TO_ACTIVE_MAX = 0;
	int m_countToActive = 0;
	int m_activeLimit = 0;

	bool m_ends = false;
};

#endif //! EFFECT_H
