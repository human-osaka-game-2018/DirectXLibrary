/// <filename>
/// EffectManager.cpp
/// </filename>
/// <summary>
/// エフェクト管理クラスのソース
/// </summary>

#include "EffectManager.h"

#include <Windows.h>

#include <vector>

#include <d3dx9.h>

#include "Effect\Effect.h"

void EffectManager::AddEffect(Effect* pEffect)
{
	m_pEffects.push_back(pEffect);
}

void EffectManager::Update()
{
	if (m_pEffects.size() <= 0) return;

	ReleaseEndEffects();

	for (auto i : m_pEffects)
	{
		i->Update();
	}
}

void EffectManager::Render()
{
	if (m_pEffects.size() <= 0) return;

	for (auto i : m_pEffects)
	{
		i->Render();
	}
}

void EffectManager::AllRelease()
{
	for (auto i : m_pEffects)
	{
		delete i;
	}

	m_pEffects.clear();
	m_pEffects.shrink_to_fit();
}

void EffectManager::ReleaseEndEffects()
{
	if (m_pEffects.size() <= 0) return;

	for (int i = static_cast<int>(m_pEffects.size() - 1); i >= 0; --i)
	{
		if (!m_pEffects[i]->GetEnds())
		{
			continue;
		}

		delete m_pEffects[i];

		std::vector<Effect*>::iterator thisIndexItr = m_pEffects.begin() + i;

		m_pEffects.erase(thisIndexItr);
	}
}
