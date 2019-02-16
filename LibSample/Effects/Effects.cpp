/// <summary>
/// エフェクトを作る際の見本
/// 後に撤去
/// </summary>
/// 
#include "Effects.h"

#include <d3dx9.h>

#include "GameLib.h"

void GetScoreStarEffect::Update()
{
	InitActivatedParticle();

	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->GetLifeFrame() > 40)
		{
			m_ends = true;

			return;
		}

		m_particles[i]->FadeIn(0, 10);
		m_particles[i]->FadeOut(15, 20);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Update();
	}
}

void GetClearStarEffect::Update()
{
	InitActivatedParticle();

	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->GetLifeFrame() > 50)
		{
			m_ends = true;

			return;
		}

		m_particles[i]->FadeIn(0, 10);
		m_particles[i]->FadeOut(20, 25);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->CirculationZ(5.0f);
		m_particles[i]->Update();
	}
}

void GetDamageStarEffect::Update()
{
	InitActivatedParticle();

	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->GetLifeFrame() > 30)
		{
			m_ends = true;

			return;
		}

		m_particles[i]->FadeIn(0, 10);
		m_particles[i]->FadeOut(10, 20);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Update();
	}
}

void FlowerFallingEffect::Update()
{
	InitActivatedParticle();

	std::uniform_real_distribution<float> degRand(0, D3DX_PI);

	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->GetLifeFrame() > rand() % 80 + 220) Init(m_particles[i]);

		D3DXVECTOR2 gravity = { cos(degRand(m_randEngine)) , 0.0f};

		m_particles[i]->RotateX(static_cast<float>(rand() % 5));
		m_particles[i]->RotateY(static_cast<float>(rand() % 5));
		m_particles[i]->RotateZ(static_cast<float>(rand() % 5));
		m_particles[i]->Accelarate(gravity);
		m_particles[i]->Update();
	}
}
