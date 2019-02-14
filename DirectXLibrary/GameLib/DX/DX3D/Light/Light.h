/**
* @file Light.h
* @brief ライトクラスのヘッダ
*/

#ifndef LIGHT_H
#define LIGHT_H

#include <Windows.h>

#include <d3dx9.h>

/**
* @brief ライトクラス
*/
class Light
{
public:
	Light(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~Light() {};

	/**
	* @brief 引数のライト構造体のデータを用いてライトを作成しそれを使う
	* @param light ライト構造体 phi等にも値を入れる必要があるときがある
	* @param index 作成するライトに振り分ける識別番号
	*/
	inline VOID SetLight(const D3DLIGHT9& light, DWORD index) const
	{
		m_pDX_GRAPHIC_DEVICE->SetLight(index, &light);
		m_pDX_GRAPHIC_DEVICE->LightEnable(index, true);
	}

	/**
	* @brief SetLightで使用しているライトをonにする,SetLightをしたときに自動で呼ばれる
	* @param onにするライトに振り分けられた識別番号
	*/
	inline VOID OnLight(DWORD index) const
	{
		m_pDX_GRAPHIC_DEVICE->LightEnable(index, true);
	}

	/**
	* @brief SetLightで使用しているライトをoffにする
	* @param offにするライトに振り分けられた識別番号
	*/
	inline VOID OffLight(DWORD index) const
	{
		m_pDX_GRAPHIC_DEVICE->LightEnable(index, false);
	}

	/**
	* @brief ライティングを有効にする
	*/
	inline VOID EnableLighting() const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	}

	/**
	* @brief ライティングを無効にする ライトをすべて無効にする
	*/
	inline VOID DisableLighting() const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	}

	/**
	* @brief 環境光の強さを変更する 呼ばれていない場合環境光は使われない
	* @param aRGB 環境光の強さ 明るい色のほうが強くなる
	*/
	inline VOID ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_AMBIENT, aRGB);
	}

	/**
	* @brief 反射光を有効にする
	*/
	inline VOID EnableSpecular() const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);
	}

	/**
	* @brief 反射光を無効にする
	*/
	inline VOID DisaableSpecular() const
	{
		m_pDX_GRAPHIC_DEVICE->SetRenderState(D3DRS_SPECULARENABLE, false);
	}

	/**
	* @brief デフォルトのライティングを使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	VOID DefaultLighting() const
	{
		EnableLighting();
		EnableSpecular();
	}

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;
};

#endif // !LIGHT_H
