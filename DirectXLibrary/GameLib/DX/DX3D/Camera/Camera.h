/**
* @file Camera.h
* @brief カメラクラスのヘッダ
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <Windows.h>

#include <d3dx9.h>

/**
* @brief カメラクラス
*/
class Camera
{
public:
	explicit Camera(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~Camera() {};

	/**
	* @brief 現在のカメラの位置を取得する
	* @param[out] pCameraPos カメラ位置を入れる
	*/
	inline VOID GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		pCameraPos->x = m_cameraPos.x;
		pCameraPos->y = m_cameraPos.y;
		pCameraPos->z = m_cameraPos.z;
	}

	/**
	* @brief 現在のカメラの位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline VOID SetCameraPos(float x, float y, float z)
	{
		m_cameraPos.x = x;
		m_cameraPos.y = y;
		m_cameraPos.z = z;
	}

	inline VOID SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_cameraPos.x = rCameraPos.x;
		m_cameraPos.y = rCameraPos.y;
		m_cameraPos.z = rCameraPos.z;
	}

	/**
	* @brief 現在のカメラの注視点を取得する
	* @param[out] pEyePoint カメラの注視点を入れる
	*/
	inline VOID GetEyePt(D3DXVECTOR3* pEyePoint) const
	{
		pEyePoint->x = m_eyePoint.x;
		pEyePoint->y = m_eyePoint.y;
		pEyePoint->z = m_eyePoint.z;
	}

	/**
	* @brief 現在のカメラの注視点位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline VOID SetEyePt(float x, float y, float z)
	{
		m_eyePoint.x = x;
		m_eyePoint.y = y;
		m_eyePoint.z = z;
	}

	inline VOID SetEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_eyePoint.x = rEyePt.x;
		m_eyePoint.y = rEyePt.y;
		m_eyePoint.z = rEyePt.z;
	}

	/**
	* @brief カメラのビュー行列を取得する
	* @param[out] pView ビュー行列を入れる
	*/
	inline VOID GetView(D3DXMATRIX* pView) const
	{
		*pView = m_view;
	}

	/**
	* @brief カメラのプロジェクション行列を取得する
	* @param[out] pProjrction プロジェクション行列を入れる
	*/
	inline VOID GetProjection(D3DXMATRIX* pProjrction) const
	{
		*pProjrction = m_projection;
	}

	/**
	* @brief カメラを適用させる
	*/
	VOID SetTransform();

	/**
	* @brief 引数の行列をビルボード化する、
	* 回転行列なのでかけ合わせる順番は回転行列をかけ合わせるとき
	* @param[in,out] pWorld ビルボード化する行列のポインタ
	*/
	VOID TransBillBoard(D3DXMATRIX* pWorld) const;

	/// <summary>
	/// 引数のワールド座標をスクリーン座標に直した値を返す
	/// </summary>
	/// <param name="screenPos">[in]ワールド座標に直したいスクリーン座標</param>
	/// <returns>引数をワールド座標に直した値</returns>
	D3DXVECTOR3 TransScreen(const D3DXVECTOR3& screenPos);

	/// <summary>
	/// 引数のスクリーン座標をワールド座標に直した値を返す
	/// </summary>
	/// <param name="worldPos">[in]スクリーン座標に直したいワールド座標</param>
	/// <returns>引数をスクリーン座標に直した値</returns>
	D3DXVECTOR3 TransWorld(const D3DXVECTOR3& worldPos);

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;

	D3DXVECTOR3 m_cameraPos			= { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_eyePoint				= { 0.0f,0.0f,1.0f };
	D3DXVECTOR3 m_cameraOverhead	= { 0.0f,1.0f,0.0f };

	D3DXMATRIX m_view;
	D3DXMATRIX m_projection;
};

#endif //! CAMERA_H
