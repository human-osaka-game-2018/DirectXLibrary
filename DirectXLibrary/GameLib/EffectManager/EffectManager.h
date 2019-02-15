/// <filename>
/// EffectManager.h
/// </filename>
/// <summary>
/// エフェクト管理クラスのヘッダ
/// </summary>

#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include <Windows.h>

#include <vector>

#include <d3dx9.h>
	
#include "Effect\Effect.h"
#include "Effect\Effects\Enum\EFFECT_ID.h"
#include "Effect\Effects\Effects.h"

/// <summary>
/// エフェクトを管理するクラス
/// </summary>
class EffectManager
{
public:
	EffectManager() {};

	~EffectManager() 
	{
		AllRelease();
	}

	/// <summary>
	/// エフェクトの追加
	/// </summary>
	/// <param name="pEffect">追加したいエフェクトのポインタ</param>
	void AddEffect(Effect* pEffect);

	/// <summary>
	/// エフェクトの更新
	/// </summary>
	void Update();

	/// <summary>
	/// エフェクトの描画
	/// </summary>
	void Render();

	/// <summary>
	/// 全てのエフェクトの開放
	/// </summary>
	void AllRelease();

private:
	/// <summary>
	/// 終了したエフェクトの開放
	/// </summary>
	void ReleaseEndEffects();

	std::vector<Effect*> m_pEffects;
};

#endif //! EFFECT_MANAGER_H
