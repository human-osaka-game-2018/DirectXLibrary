/**
* @file VerticesParam.h
* @brief 物体の状態構造体とテクスチャの座標構造体のヘッダ
* @author Harutaka-Tsujino
*/

#ifndef VERTICES_PARAM_H
#define VERTICES_PARAM_H

#include <Windows.h>

#include <d3dx9.h>

/**
* @brief テクスチャの座標
*/
struct TexUV
{
public:
	float m_startTU = 0.0f;
	float m_startTV = 0.0f;
	float m_endTU = 1.0f;
	float m_endTV = 1.0f;
};

typedef D3DXVECTOR3 RotateValueXYZ;

/**
* @brief 頂点情報配列を作成するためのデータ
*/
struct VerticesParam
{
public:
	D3DXVECTOR3 m_center	= { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 m_halfScale = { 0.0f, 0.0f, 0.0f };

	RotateValueXYZ m_deg = { 0.0f, 0.0f, 0.0f };

	DWORD m_aRGB = 0xFFFFFFFF;
	TexUV m_texUV;
};

#endif //! VERTICES_PARAM_H
