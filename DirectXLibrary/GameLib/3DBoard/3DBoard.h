#ifndef BOARD_3D_H_
#define BOARD_3D_H_

#include <Windows.h>

#include <d3dx9.h>

#include "../DX/DX3D/CustomVertexEditor/Data/VerticesParam.h"

/**
* @brief 3Dを描画するにあたって必要な頂点情報
*/
struct Vertex3D
{
public:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Normal;
	DWORD		m_Color;
	float		m_Tu;
	float		m_Tv;
};

class Board3D
{
public:
	Board3D() {}
	~Board3D() {}

	void CreateRect(Vertex3D* p3DVertices, const D3DXVECTOR3& halfScale, const D3DXVECTOR3& center,
		DWORD aRGB = 0xFFFFFFFF, float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f);

	void CreateRect(Vertex3D* p3DVertices, const VerticesParam& verticesParam);
};


#endif // !BOARD_3D_H_
