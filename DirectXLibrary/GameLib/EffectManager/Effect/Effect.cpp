#include "Effect.h"

#include <Windows.h>

#include <d3dx9.h>

#include <vector>

#include "Particle/Particle.h"

VOID Effect::CountUpActiveLimit()
{
	if (m_COUNT_TO_ACTIVE_MAX == 0)
	{
		m_activeLimit = static_cast<int>(m_particles.size());

		return;
	}

	++m_countToActive;

	if (m_countToActive >= m_COUNT_TO_ACTIVE_MAX - 1)
	{
		m_countToActive = 0;

		++m_activeLimit;
	}

	int particleSize = static_cast<int>(m_particles.size());

	if (m_activeLimit >= particleSize) m_activeLimit = particleSize;
}
