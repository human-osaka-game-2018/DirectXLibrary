/// <summary>
/// エフェクトを作る際の見本
/// 後に撤去
/// </summary>
/// 
#include "Effects.h"

#include "../Effect.h"
#include "VerticesParam.h"
#include "CustomVertex.h"

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

void MouseCursorEffect::Update()
{
	m_rGameLib.CreateTex(_T("2DTextures/EffectTexture/Star.png"), _T("2DTextures/EffectTexture/Star.png"));

	InitActivatedParticle();

	POINT cursorPos;
	m_rGameLib.CursorPos(&cursorPos);
	D3DXVECTOR3 center = { static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y), 0.0f };
	D3DXVECTOR2 gravity = { 0.0f, 0.1f };

	InitCursor(m_particles[0]);
	m_particles[0]->RotateZ(5.0f);
	m_particles[0]->Update();

	for (int i = 1; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->GetLifeFrame() > 60) Init(m_particles[i]);

		m_particles[i]->FadeIn(0, 10);
		m_particles[i]->FadeOut(30, 25);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Accelarate(gravity);
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
