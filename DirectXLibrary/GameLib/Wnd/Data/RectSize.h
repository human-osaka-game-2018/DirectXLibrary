/**
* @file RectSize.h
* @brief 平面上の値構造体のヘッダ
*/

#ifndef RECT_SIZE_H
#define RECT_SIZE_H

#include <Windows.h>

#include <d3dx9.h>

/**
* @brief 平面上で用いられるサイズなどの値
*/
struct RectSize
{
public:
	inline VOID TransD3DXVECTOR3(D3DXVECTOR3* pVec3) const
	{
		*pVec3 = { static_cast<float>(m_x), static_cast<float>(m_y), 0.0f };
	}

	int m_x = 0;
	int m_y = 0;
};

#endif //! RECT_SIZE_H
