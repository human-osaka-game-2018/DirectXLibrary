/// <filename>
/// Effect.cpp
/// </filename>
/// <summary>
/// エフェクト基底クラスのソース
/// </summary>

#include "Effect.h"

#include <Windows.h>

#include <d3dx9.h>

#include <vector>

#include "IGameLibRenderer\IGameLibRenderer.h"
#include "Particle/Particle.h"
#include "Algorithm\Algorithm.h"

void Effect::Render()
{
	m_pIGameLibRenderer->AddtionBlendMode();

	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		m_particles[i]->Render();
	}

	m_pIGameLibRenderer->DefaultBlendMode();

	CountUpActiveLimit();
}

void Effect::CountUpActiveLimit()
{
	//! m_COUNT_TO_ACTIVE_MAXが0の場合全てのパーティクルをアクティベートする
	if (m_COUNT_TO_ACTIVE_MAX == 0)
	{
		m_activeLimit = static_cast<int>(m_particles.size());

		return;
	}

	auto CountActivelimitUp = [this]() {++m_activeLimit; };
	Algorithm::CountUp_s(&m_countToActive, m_COUNT_TO_ACTIVE_MAX - 1, CountActivelimitUp);

	int particleSize = static_cast<int>(m_particles.size());

	if (m_activeLimit >= particleSize) m_activeLimit = particleSize;
}

void Effect::InitActivatedParticle()
{
	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (i == m_activeLimit && m_countToActive == 0 && m_COUNT_TO_ACTIVE_MAX != 0)
		{
			Init(m_particles[i]);

			break;
		}
	}
}
