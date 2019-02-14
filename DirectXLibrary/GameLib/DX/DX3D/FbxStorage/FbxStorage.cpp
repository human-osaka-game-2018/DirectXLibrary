/// <filename>
/// FbxStorage.h
/// </filename>
/// <summary>
/// Fbxの保管を行うクラスのソース
/// </summary>

#include "FbxStorage.h"

#include <Windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

#include "FbxRelated/FbxRelated.h"

VOID FbxStorage::CreateFbx(const TCHAR* pKey, const CHAR* pFilePath)
{
	m_pFbxRelatedMap[pKey] = new FbxRelated(m_pDX_GRAPHIC_DEVICE);
	m_pFbxRelatedMap[pKey]->LoadFbx(pFilePath);
}
