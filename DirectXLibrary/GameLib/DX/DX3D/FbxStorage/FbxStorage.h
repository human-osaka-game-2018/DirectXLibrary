/// <filename>
/// FbxStorage.h
/// </filename>
/// <summary>
/// Fbxの保管を行うクラスのヘッダ
/// </summary>

#ifndef FBX_STORAGE_H
#define FBX_STORAGE_H

#include <Windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

#include "FbxRelated/FbxRelated.h"

/// <summary>
/// Fbxの保管を行うクラス
/// </summary>
class FbxStorage
{
public:
	explicit FbxStorage(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~FbxStorage() 
	{
		for (auto pI : m_pFbxRelatedMap)
		{
			//! deleteだけでなくリリースの呼び忘れ注意
			pI.second->Release();

			delete pI.second;
		}

		m_pFbxRelatedMap.clear();
	}

	/// <summary>
	/// FBXオブジェクトの作成を行う
	/// </summary>
	/// <param name="pKey">[in]作成するオブジェクトにつけるキー</param>
	/// <param name="pFilePath">[in]作成するオブジェクトのパス</param>
	VOID CreateFbx(const TCHAR* pKey, const CHAR* pFilePath);

	/// <summary>
	/// FBXオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">[in]取得したいオブジェクトのキー</param>
	/// <returns>FBXオブジェクトクラスの参照</returns>
	inline FbxRelated& GetFbx(const TCHAR* pKey)
	{
		return *m_pFbxRelatedMap[pKey];
	}

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;

	std::map<const TCHAR*, FbxRelated*> m_pFbxRelatedMap;
};

#endif // !FBX_STORAGE_H
