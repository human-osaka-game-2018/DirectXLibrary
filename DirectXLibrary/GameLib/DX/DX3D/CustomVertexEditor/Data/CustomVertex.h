/**
* @file CustomVertex.h
* @brief 頂点データ構造体のヘッダ
* @author Harutaka-Tsujino
*/

#ifndef CUSTOM_VERTEX_H
#define CUSTOM_VERTEX_H

#include <Windows.h>
#include <d3dx9.h>

/**
* @brief 頂点データ
*/
struct CustomVertex
{
public:
	D3DXVECTOR3 m_pos;

	//! 重みの逆数 基本1
	float m_rHW = 1.0f;

	DWORD m_aRGB = 0xFFFFFFFF;

	//! テクスチャの座標
	D3DXVECTOR2 m_texUV;

	static const int m_RECT_VERTICES_NUM = 4;
};

#endif // !CUSTOM_VERTEX_H
