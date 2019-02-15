/**
* @file TexStorage.h
* @brief テクスチャ保管クラスのヘッダ
*/

#ifndef TEX_STORAGE_H
#define TEX_STORAGE_H

#include <Windows.h>
#include <tchar.h>

#include <map>

#include <d3dx9.h>

/**
* @brief テクスチャを作成保存しそれを渡したりするクラス
*/
class TexStorage
{
public:
	TexStorage(const LPDIRECT3DDEVICE9 dXGraphicDevice) :m_pDX_GRAPHIC_DEVICE(dXGraphicDevice) {};
	~TexStorage()
	{
		AllRelease();
	}

	/**
	* @brief テクスチャを作成する
	* @param pTexKey テクスチャにつける名前のポインタ キー 連想配列
	* @param pTexPath 画像のパスのポインタ
	*/
	inline void CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		if (Exists(pTexKey)) return;

		D3DXCreateTextureFromFile(
			m_pDX_GRAPHIC_DEVICE, 
			pTexPath, 
			&m_pTexMap[pTexKey]);
	}

	/**
	* @brief 全てのテクスチャの開放
	*/
	inline void AllRelease()
	{
		for (auto i : m_pTexMap)
		{
			if (!i.second) continue;

			(i.second)->Release();
		}

		m_pTexMap.clear();
	}

	/// <summary>
	/// 指定したテクスチャの開放を行う
	/// </summary>
	/// <param name="pTexKey">[in]開放したいテクスチャのパス</param>
	inline void Release(const TCHAR* pTexKey)
	{
		if (!Exists(pTexKey)) return;

		m_pTexMap[pTexKey]->Release();
		m_pTexMap.erase(pTexKey);
	}

	/**
	* @brief テクスチャを取得する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return テクスチャのポインタ
	*/
	inline const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey)
	{
		return m_pTexMap[pTexKey];
	}

	/**
	* @brief テクスチャが生成されているか判断する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return 存在していたらtrue
	*/
	inline const bool Exists(const TCHAR* pTexKey) const
	{
		return (m_pTexMap.find(pTexKey) != m_pTexMap.end());
	}

private:
	const LPDIRECT3DDEVICE9 m_pDX_GRAPHIC_DEVICE = nullptr;

	std::map<const TCHAR*, LPDIRECT3DTEXTURE9> m_pTexMap;
};

#endif //! TEX_STORAGE_H
