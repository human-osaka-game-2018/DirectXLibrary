#include "3DBoard.h"

VOID Board3D::CreateRect(Vertex3D* p3DVertices, const D3DXVECTOR3& halfScale, const D3DXVECTOR3& center,
	DWORD aRGB, float startTU, float startTV, float endTU, float endTV)
{
	const int m_RECT_VERTICES_NUM = 4;

	for (int i = 0; i < m_RECT_VERTICES_NUM; ++i)
	{
		p3DVertices[i].m_Pos = center;
		p3DVertices[i].m_Pos.x += (i % 3) ? halfScale.x : -halfScale.x;
		p3DVertices[i].m_Pos.y += (i / 2) ? halfScale.y : -halfScale.y;

		p3DVertices[i].m_Color = aRGB;

		p3DVertices[i].m_Tu = (i % 3) ? endTU : startTU;
		p3DVertices[i].m_Tv = (i / 2) ? endTV : startTV;

		p3DVertices[i].m_Normal.x = 0.f;
		p3DVertices[i].m_Normal.y = 0.f;
		p3DVertices[i].m_Normal.z = -1.f;
	}
}

VOID Board3D::CreateRect(Vertex3D* p3DVertices, const VerticesParam& verticesParam)
{
	CreateRect(
		p3DVertices,
		verticesParam.m_halfScale, verticesParam.m_center,
		verticesParam.m_aRGB,
		verticesParam.m_texUV.m_startTU, verticesParam.m_texUV.m_startTV,
		verticesParam.m_texUV.m_endTU, verticesParam.m_texUV.m_endTV
	);
}
