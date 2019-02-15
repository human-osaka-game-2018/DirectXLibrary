/// <filename>
/// Camera.cpp
/// </filename>
/// <summary>
/// カメラクラスのソース
/// </summary>

#include "Camera.h"

#include <Windows.h>

#include <d3dx9.h>

void Camera::SetTransform()
{
	D3DXMatrixLookAtLH(
		&m_view,
		&m_cameraPos,
		&m_eyePoint,
		&m_cameraOverhead);

	m_pDX_GRAPHIC_DEVICE->SetTransform(D3DTS_VIEW, &m_view);

	D3DVIEWPORT9 viewPort;
	m_pDX_GRAPHIC_DEVICE->GetViewport(&viewPort);
	float aspect = static_cast<float>(viewPort.Width) / static_cast<float>(viewPort.Height);

	const int DEFAULT_EYE_RADIAN = 60;

	//! nearを0.0fにすると全ての物体のz値が0.0fになる
	const float DEFAULT_NEAR	= 0.01f;
	const float DEFAULT_FAR		= 10000.0f;

	D3DXMatrixPerspectiveFovLH(
		&m_projection,
		D3DXToRadian(DEFAULT_EYE_RADIAN),
		aspect,
		DEFAULT_NEAR,
		DEFAULT_FAR);

	m_pDX_GRAPHIC_DEVICE->SetTransform(D3DTS_PROJECTION, &m_projection);
}

D3DXVECTOR3 Camera::TransScreen(const D3DXVECTOR3& worldPos)
{
	D3DVIEWPORT9 viewPort;
	m_pDX_GRAPHIC_DEVICE->GetViewport(&viewPort);

	D3DXVECTOR2 screenMat(static_cast<float>(viewPort.Width * 0.5f),
		static_cast<float>(viewPort.Height * 0.5f));

	D3DXMATRIX viewPortMat =
	{
		screenMat.x ,	0 ,				0 , 0 ,
		0 ,				-screenMat.y ,	0 , 0 ,
		0 ,				0 ,				1 , 0 ,
		screenMat.x ,	screenMat.y ,	0 , 1
	};

	D3DXVECTOR3 screenPos, tmp;
	D3DXVec3TransformCoord(&tmp, &worldPos, &m_view);
	D3DXVec3TransformCoord(&tmp, &tmp, &m_projection);

	//! Z値を1.0に固定する
	tmp.x /= tmp.z;
	tmp.y /= tmp.z;
	tmp.z /= tmp.z;

	D3DXVec3TransformCoord(&screenPos, &tmp, &viewPortMat);

	return screenPos;
}

D3DXVECTOR3 Camera::TransWorld(const D3DXVECTOR3& screenPos)
{
	D3DVIEWPORT9 viewPort;
	m_pDX_GRAPHIC_DEVICE->GetViewport(&viewPort);

	D3DXVECTOR2 screen(static_cast<float>(viewPort.Width * 0.5f),
		static_cast<float>(viewPort.Height * 0.5f));

	//! 各行列の逆行列を算出
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &m_view);

	D3DXMATRIX invProjection;
	D3DXMatrixInverse(&invProjection, NULL, &m_projection);

	D3DXMATRIX viewPortMat =
	{
		screen.x, 0 ,		 0, 0,
		0,		  -screen.y, 0, 0,
		0,		  0  ,		 1, 0,
		screen.x, screen.y,  0, 1
	};

	D3DXMATRIX invViewport;
	D3DXMatrixInverse(&invViewport, NULL, &viewPortMat);

	//! スクリーン変換の過程を逆にする
	D3DXMATRIX tmp = invViewport * invProjection * invView;
	D3DXVECTOR3 worldPos;

	D3DXVec3TransformCoord(&worldPos, &screenPos, &tmp);

	return worldPos;
}

void Camera::TransBillBoard(D3DXMATRIX* pWorld) const
{
	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(
		&viewInverse,
		NULL,
		&m_view);

	//! 移動にかかわる部分の削除
	viewInverse._41 = viewInverse._42 = viewInverse._43 = 0.0f;

	D3DXMatrixMultiply(
		pWorld,
		pWorld,
		&viewInverse);
}
