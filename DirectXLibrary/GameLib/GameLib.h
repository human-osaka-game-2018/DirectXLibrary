﻿/**
* @file GameLib.h
* @brief 汎用クラスのFacadeのヘッダ
*/

#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "IGameLibRenderer\IGameLibRenderer.h"
#include "../Class/Singleton/Singleton.h"
#include "Wnd\Wnd.h"
#include "DX\DX.h"
#include "CustomVertex.h"
#include "VerticesParam.h"
#include "TimerManager\TimerManager.h"
#include "Collision\Collision.h"
#include "3DBoard\3DBoard.h"
#include "Sound\Sound.h"
#include "JoyconManager\JoyconManager.h"
#include "EffectManager\EffectManager.h"
#include "XInputManager\XinputManager.h"

template<typename T>
void SafeRelease(T** ppType)
{
	delete (*ppType);
	*ppType = nullptr;
}

/**
* @brief 汎用クラスのFacade,ウィンドウ生成やDX関係の初期化も行う
*/
class GameLib :public IGameLibRenderer, public Singleton<GameLib>
{
public:
	friend class Singleton<GameLib>;

	~GameLib()
	{
		delete m_pEffectManager;
		delete m_pSound;
		delete m_pBoard3D;
		delete m_pCollision;
		delete m_pDX;
		delete m_pWnd;
		delete m_pJoyconManager;
		delete m_pXinputManager;
	}

	/**
	* @brief ウィンドウを生成しDX関係を初期化する,一番初めにこれを呼ぶ
	* @param hInst インスタンスのハンドル
	* @param pAppName アプリケーションの名前のポインタ
	*/
	inline static void Create(const HINSTANCE hInst, const TCHAR* pAppName)
	{
		if (!m_pWnd)			m_pWnd			 = new Wnd(hInst, pAppName);
		if (!m_pDX)				m_pDX			 = new DX(m_pWnd->GetHWND(), m_pWnd->GetWndSize());
		if (!m_pCollision)		m_pCollision	 = new Collision();
		if (!m_pSound)			m_pSound		 = new Sound();
		if (!m_pBoard3D)		m_pBoard3D		 = new Board3D();
		if (!m_pJoyconManager)	m_pJoyconManager = new JoyconManager();
		if (!m_pXinputManager)  m_pXinputManager = new XinputManager();
	}

	/**
	* @brief メッセージループを作成し引数で与えられた関数を60fpsで回す
	* @param メッセージループで回す関数のポインタ
	*/
	void RunFunc(void(*pMainFunc)());

	/**
	* @brief クライアント領域をm_WND_SIZEと同じにする
	*/
	inline void ResizeWnd() const
	{
		m_pWnd->ResizeWnd();
	}

	/// <summary>
	/// ウィンドウのサイズを取得する
	/// </summary>
	/// <returns>ウィンドウのサイズ</returns>
	/// <seealso cref="RectSize"/>
	inline RectSize GetWndSize() const
	{
		m_pWnd->GetWndSize();
	}

	/**
	* @brief ウィンドウモードの切替,3Dデバイスがロストする危険性がある
	*/
	void ToggleWndMode()
	{
		m_pDX->ToggleWndMode();
	}

	/**
	* @brief 色の合成を通常合成に変更する デフォルトでは通常合成になっている
	*/
	inline void DefaultBlendMode() const
	{
		m_pDX->DefaultBlendMode();
	}

	/**
	* @brief 色の合成を加算合成に変更する
	*/
	inline void AddtionBlendMode() const
	{
		m_pDX->AddtionBlendMode();
	}

	/**
	* @brief デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline void DefaultColorBlending() const
	{
		m_pDX->DefaultColorBlending();
	}

	/**
	* @brief 引数のライト構造体のデータを用いてライトを作成しそれを使う
	* @param light ライト構造体 phi等にも値を入れる必要があるときがある
	* @param index 作成するライトに振り分ける識別番号
	*/
	inline void SetLight(const D3DLIGHT9& rLight, DWORD index) const
	{
		m_pDX->SetLight(rLight, index);
	}

	/**
	* @brief SetLightで使用しているライトをonにする,SetLightをしたときに自動で呼ばれる
	* @param onにするライトに振り分けられた識別番号
	*/
	inline void OnLight(DWORD index) const
	{
		m_pDX->OnLight(index);
	}

	/**
	* @brief SetLightで使用しているライトをoffにする
	* @param offにするライトに振り分けられた識別番号
	*/
	inline void OffLight(DWORD index) const
	{
		m_pDX->OffLight(index);
	}

	/**
	* @brief ライティングを有効にする
	*/
	inline void EnableLighting() const
	{
		m_pDX->EnableLighting();
	}

	/**
	* @brief ライティングを無効にする ライトをすべて無効にする
	*/
	inline void DisableLighting() const
	{
		m_pDX->DisableLighting();
	}

	/**
	* @brief 環境光の強さを変更する 呼ばれていない場合環境光は使われない
	* @param aRGB 環境光の強さ 明るい色のほうが強くなる
	*/
	inline void ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_pDX->ChangeAmbientIntensity(aRGB);
	}

	/**
	* @brief 反射光を有効にする
	*/
	inline void EnableSpecular() const
	{
		m_pDX->EnableSpecular();
	}

	/**
	* @brief 反射光を無効にする
	*/
	inline void DisaableSpecular() const
	{
		m_pDX->DisaableSpecular();
	}

	/**
	* @brief デフォルトのライティングを使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline void DefaultLighting() const
	{
		m_pDX->DefaultLighting();
	}

	/**
	* @brief テクスチャを作成する
	* @param pTexKey テクスチャにつける名前のポインタ キー 連想配列
	* @param pTexPath 画像のパスのポインタ
	*/
	inline void CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		m_pDX->CreateTex(pTexKey, pTexPath);
	}

	/**
	* @brief 全てのテクスチャの開放
	*/
	inline void AllTexRelease()
	{
		m_pDX->AllTexRelease();
	}

	/// <summary>
	/// 指定したテクスチャの開放を行う
	/// </summary>
	/// <param name="pTexKey">[in]開放したいテクスチャのパス</param>
	inline void ReleaseTex(const TCHAR* pTexKey)
	{
		m_pDX->ReleaseTex(pTexKey);
	}

	/**
	* @brief テクスチャを取得する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return テクスチャのポインタ
	*/
	inline const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey) const
	{
		return m_pDX->GetTex(pTexKey);
	}
	/**
	* @brief テクスチャが生成されているか判断する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return 存在していたらtrue
	*/
	inline const bool TexExists(const TCHAR* pTexKey) const
	{
		return m_pDX->TexExists(pTexKey);
	}

	/**
	* @brief 現在のカメラの位置を取得する
	* @param[out] pCameraPos カメラ位置を入れる
	*/
	inline void GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		m_pDX->GetCameraPos(pCameraPos);
	}

	/**
	* @brief 現在のカメラの位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline void SetCameraPos(float x, float y, float z)
	{
		m_pDX->SetCameraPos(x, y, z);
	}

	inline void SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_pDX->SetCameraPos(rCameraPos);
	}

	/**
	* @brief 現在のカメラの注視点を取得する
	* @param[out] pEyePoint カメラの注視点を入れる
	*/
	inline void GetCameraEyePt(D3DXVECTOR3* pEyePoint) const
	{
		m_pDX->GetCameraPos(pEyePoint);
	}

	/**
	* @brief 現在のカメラの注視点位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline void SetCameraEyePt(float x, float y, float z)
	{
		m_pDX->SetCameraEyePt(x, y, z);
	}

	inline void SetCameraEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_pDX->SetCameraEyePt(rEyePt);
	}

	/**
	* @brief カメラのビュー行列を取得する
	* @param[out] pView ビュー行列を入れる
	*/
	inline void GetView(D3DXMATRIX* pView) const
	{
		m_pDX->GetView(pView);
	}

	/**
	* @brief カメラのプロジェクション行列を取得する
	* @param[out] pProjrction プロジェクション行列を入れる
	*/
	inline void GetProjection(D3DXMATRIX* pProjrction) const
	{
		m_pDX->GetProjection(pProjrction);
	}

	/**
	* @brief カメラを適用させる
	*/
	inline void SetCameraTransform()
	{
		m_pDX->SetCameraTransform();
	}

	/**
	* @brief 引数の行列をビルボード化する、
	* 回転行列なのでかけ合わせる順番は回転行列をかけ合わせるとき
	* @param[in,out] pWorld ビルボード化する行列のポインタ
	*/
	inline void TransBillBoard(D3DXMATRIX* pWorld) const
	{
		m_pDX->TransBillBoard(pWorld);
	}

	/// <summary>
	/// 引数のワールド座標をスクリーン座標に直した値を返す
	/// </summary>
	/// <param name="screenPos">[in]ワールド座標に直したいスクリーン座標</param>
	/// <returns>引数をワールド座標に直した値</returns>
	inline D3DXVECTOR3 TransScreen(const D3DXVECTOR3& Pos)
	{
		return m_pDX->TransScreen(Pos);
	}

	/// <summary>
	/// 引数のスクリーン座標をワールド座標に直した値を返す
	/// </summary>
	/// <param name="worldPos">[in]スクリーン座標に直したいワールド座標</param>
	/// <returns>引数をスクリーン座標に直した値</returns>
	inline D3DXVECTOR3 TransWorld(const D3DXVECTOR3& Pos)
	{
		return m_pDX->TransWorld(Pos);
	}

	/**
	* @brief XYZ順に回転を行う
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param deg 回転をさせる度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	* @detail 回転行列を作成し、矩形の中心を求め回転の中心を原点に移動させ、回転行列を用いて回転を行い原点へ移動させた分元に戻す
	*/
	inline void RotateRectXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3& deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectXYZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief x軸で回転させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param 度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	*/
	inline void RotateRectX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectX(pCustomVertices, deg, relativeRotateCenter);
	}

	inline void RotateRectY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectY(pCustomVertices, deg, relativeRotateCenter);
	}

	inline void RotateRectZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief 矩形を拡縮させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param scaleRate 拡縮率
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	inline void RescaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const
	{
		m_pDX->RescaleRect(pCustomVertices, scaleRate);
	}

	/**
	* @brief 矩形を移動させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param movement 移動量
	*/
	inline void MoveRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const
	{
		m_pDX->MoveRect(pCustomVertices, movement);
	}

	/**
	* @brief 矩形を引数の位置に再配置させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param pos 矩形を移動させる座標
	*/
	inline void LocaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const
	{
		m_pDX->LocaleRect(pCustomVertices, pos);
	}

	/**
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param startTU x方向のテクスチャ座標の始まりの値
	* @param startTV y方向のテクスチャ座標の始まりの値
	* @param endTU x方向のテクスチャ座標の終わりの値
	* @param endTV y方向のテクスチャ座標の終わりの値
	*/
	inline void SetRectTexUV(CustomVertex* pCustomVertices,
		float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const
	{
		m_pDX->SetRectTexUV(pCustomVertices, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief 矩形の色を引数の色に変更する
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param aRGB アルファ値入りのカラーコード ARGB
	*/
	inline void SetRectARGB(CustomVertex *pCustomVertices, DWORD aRGB) const
	{
		m_pDX->SetRectARGB(pCustomVertices, aRGB);
	}

	/// <summary>
	/// 矩形を上から下にグラデーションさせる
	/// </summary>
	/// <param name="pCustomVertices">[out]グラデーションさせたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="topARGB">上の色</param>
	/// <param name="bottomARGB">下の色</param>
	inline void SetTopBottomARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX->SetTopBottomARGB(pCustomVertices, topARGB, bottomARGB);
	}

	/// <summary>
	/// 矩形を左から右にグラデーションさせる
	/// </summary>
	inline void SetLeftRightARGB(CustomVertex *pCustomVertices, DWORD leftARGB, DWORD rightARGB) const
	{
		m_pDX->SetLeftRightARGB(pCustomVertices, leftARGB, rightARGB);
	}

	/// <summary>
	/// 矩形を左上から右下にグラデーションさせる
	/// </summary>
	inline void SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX->SetObliqueToBottomRightARGB(pCustomVertices, topARGB, bottomARGB);
	}

	/// <summary>
	/// 矩形を右上から左下にグラデーションさせる
	/// </summary>
	inline void SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX->SetObliqueToBottomLeftARGB(pCustomVertices, topARGB, bottomARGB);
	}

	/// <summary>
	/// 矩形を点滅させる
	/// </summary>
	/// <param name="pVertices">[out]点滅させたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="pFrameCnt">[in,out]点滅の強度を決めるためのカウント</param>
	/// <param name="flashFlameMax">何フレームで一周期を終えるか</param>
	/// <param name="alphaMax">アルファ値の最大値</param>
	/// <param name="alphaMin">アルファ値の最小値</param>
	/// <remarks>pFrameCntは関数内で自動で増減させるのでstaticかつ関数外で値を変えてはいけない</remarks>
	inline void FlashRect(CustomVertex* pVertices, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const
	{
		m_pDX->FlashRect(pVertices, pFrameCnt, flashFlameMax, alphaMax, alphaMin);
	}

	inline void FlashRect(VerticesParam* pVerticesParam, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const
	{
		m_pDX->FlashRect(pVerticesParam, pFrameCnt, flashFlameMax, alphaMax, alphaMin);
	}

	/// <summary>
	/// フレームではなく一フレームの経過秒で矩形を点滅させる 
	/// </summary>
	/// <param name="pVertices">[out]点滅させたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="pSecondsCnt">[in,out]点滅の強度を決めるためのカウント(秒)</param>
	/// <param name="flashSecondsMax">何秒で一周期を終えるか</param>
	/// <param name="alphaMax">アルファ値の最大値</param>
	/// <param name="alphaMin">アルファ値の最小値</param>
	/// <remarks>pSecondsCntは関数内で自動で増減させるのでstaticかつ関数外で値を変えてはいけない</remarks>
	inline void FlashRect(CustomVertex* pVertices, float* pSecondsCnt, float flashSecondsMax, BYTE alphaMax, BYTE alphaMin = 0) const
	{
		m_pDX->FlashRect(pVertices, pSecondsCnt, flashSecondsMax, alphaMax, alphaMin);
	}

	inline void FlashRect(VerticesParam* pVerticesParam, float* pSecondsCnt, float flashSecondsMax, BYTE alphaMax, BYTE alphaMin = 0) const
	{
		m_pDX->FlashRect(pVerticesParam, pSecondsCnt, flashSecondsMax, alphaMax, alphaMin);
	}

	/// <summary>
	/// アルファ値のみを変更する
	/// </summary>
	/// <param name="pVerticesParam">矩形の頂点情報のデータ</param>
	/// <param name="alpha">変更したいアルファ値</param>
	inline void SetRectAlpha(VerticesParam* pVerticesParam, BYTE alpha) const
	{
		m_pDX->SetRectAlpha(pVerticesParam, alpha);
	}

	inline void SetRectAlpha(CustomVertex* pVertices, BYTE alpha) const
	{
		m_pDX->SetRectAlpha(pVertices, alpha);
	}

	/**
	* @brief 頂点データ構造体を引数の値から作成する
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param center 矩形の中心
	* @param halfScale 矩形の高さ幅の半分
	* @param aRGB 頂点の色カラーコード
	* @param startTU x方向のテクスチャ座標の始まりの値
	* @param startTV y方向のテクスチャ座標の始まりの値
	* @param endTU x方向のテクスチャ座標の終わりの値
	* @param endTV y方向のテクスチャ座標の終わりの値
	*/
	inline void CreateRect(CustomVertex *pCustomVertices, const D3DXVECTOR3& center, const D3DXVECTOR3& halfScale,
		DWORD aRGB = 0xFFFFFFFF, float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const
	{
		m_pDX->CreateRect(pCustomVertices, center, halfScale, aRGB, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief 頂点データ構造体を引数の値から作成する 回転も行う
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param verticesParam オブジェクトの状態構造体
	*/
	inline void CreateRect(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const
	{
		m_pDX->CreateRect(pCustomVertices, verticesParam);
	}

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline void Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(rFBXModel, rWorld, pTexture);
	}

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	inline void Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(pCustomVertices, pTexture);
	}

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline void Render(const Vertex3D* pVertex3D, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr)
	{
		m_pDX->Render(pVertex3D, rWorld, pTexture);
	}

	/// <summary>
	/// 文字の描画を行う
	/// </summary>
	/// <param name="topLeft">[in]左上の座標</param>
	/// <param name="pText">[in]描画したい文字列</param>
	/// <param name="format">文字のフォーマット DT_LEFT(左寄せ)等</param>
	/// <param name="pFont">描画する際に使うフォントオブジェクト</param>
	/// <param name="color">文字の色ARGB</param>
	inline void Render(const D3DXVECTOR2& topLeft, const TCHAR* pText, UINT format, LPD3DXFONT pFont, DWORD color)
	{
		m_pDX->Render(topLeft, pText, format, pFont, color);
	}

	/// <summary>
	/// 矩形の描画を行う
	/// </summary>
	/// <param name="verticesParam">頂点情報配列を作成するためのデータ</param>
	/// <param name="pTexture">矩形に張り付けるテクスチャのポインタ</param>
	inline void Render(const VerticesParam& verticesParam, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(verticesParam, pTexture);
	}

	/// <summary>
	/// FBXオブジェクトの作成を行う
	/// </summary>
	/// <param name="pKey">[in]作成するオブジェクトにつけるキー</param>
	/// <param name="pFilePath">[in]作成するオブジェクトのパス</param>
	inline void CreateFbx(const TCHAR* pKey, const CHAR* pFilePath)
	{
		m_pDX->CreateFbx(pKey, pFilePath);
	}

	/// <summary>
	/// FBXオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">[in]取得したいオブジェクトのキー</param>
	/// <returns>FBXオブジェクトクラスの参照</returns>
	inline FbxRelated& GetFbx(const TCHAR* pKey)
	{
		return m_pDX->GetFbx(pKey);
	}

	/// <summary>
	/// フォントの全開放
	/// </summary>
	inline void AllFontRelease()
	{
		m_pDX->AllFontRelease();
	}

	/// <summary>
	/// 指定したフォントの開放
	/// </summary>
	/// <param name="pFontKey">開放したいフォントのキー</param>
	inline void ReleaseFont(const TCHAR* pFontKey)
	{
		m_pDX->ReleaseFont(pFontKey);
	}

	/// <summary>
	///	フォントオブジェクトの作成
	/// </summary>
	/// <param name="pKey">作成するオブジェクトにつけるキー</param>
	/// <param name="scale">文字の幅</param>
	/// <param name="pFontName">フォントの名前 MSゴシック等</param>
	/// <param name="thickness">文字の太さ</param>
	inline void CreateFont(const TCHAR* pKey, D3DXVECTOR2 scale, const TCHAR* pFontName, UINT thickness = 0)
	{
		m_pDX->CreateFont(pKey, scale, pFontName, thickness);
	}

	/// <summary>
	/// 文字が存在しているかを判別する
	/// </summary>
	/// <param name="pKey">判別したいフォントのキー</param>
	/// <returns>存在していればtrue</returns>
	inline bool FontExists(const TCHAR* pKey)
	{
		return m_pDX->FontExists(pKey);
	}

	/// <summary>
	/// フォントオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">取得したいフォントのキー</param>
	/// <returns>フォントオブジェクトの参照</returns>
	inline const LPD3DXFONT GetFont(const TCHAR* pKey)
	{
		return m_pDX->GetFont(pKey);
	}

	/// <summary>
	/// 引数に渡したボタンが押された瞬間か
	/// </summary>
	/// <param name="key">ボタンの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool MouseIsPressed(int key) const
	{
		return m_pDX->MouseIsPressed(key);
	}

	inline bool MouseIsHeld(int key) const
	{
		return m_pDX->MouseIsHeld(key);
	}

	inline bool MouseIsReleased(int key) const
	{
		return m_pDX->MouseIsReleased(key);
	}

	inline bool MouseIsNeutral(int key) const
	{
		return m_pDX->MouseIsNeutral(key);
	}

	/// <summary>
	/// 何かのボタンが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool MouseAnyKeyIsPressed() const
	{
		return m_pDX->MouseAnyKeyIsPressed();
	}

	/// <summary>
	/// カーソルの位置の取得
	/// </summary>
	/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
	inline void CursorPos(POINT* pPos) const
	{
		m_pDX->CursorPos(pPos);
	}

	/// <summary>
	/// 前フレームからどのくらいスクロールされたか
	/// </summary>
	/// <returns>スクロールされた量</returns>
	inline long MouseWheelScrollingFromPrev() const
	{
		return m_pDX->MouseWheelScrollingFromPrev();
	}

	/// <summary>
	/// 引数に渡したキーが押された瞬間か
	/// </summary>
	/// <param name="key">キーの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool KeyboardIsPressed(int key) const
	{
		return m_pDX->KeyboardIsPressed(key);
	}

	inline bool KeyboardIsHeld(int key) const
	{
		return m_pDX->KeyboardIsHeld(key);
	}

	inline bool KeyboardIsReleased(int key) const
	{
		return m_pDX->KeyboardIsReleased(key);
	}

	inline bool KeyboardIsNeutral(int key) const
	{
		return m_pDX->KeyboardIsNeutral(key);
	}

	/// <summary>
	/// 何かのキーが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool KeyboardAnyKeyIsPressed() const
	{
		return m_pDX->KeyboardAnyKeyIsPressed();
	}

	/// <summary>
	/// 円と円の衝突判定を返す、衝突していればtrue
	/// </summary>
	/// <param name="pAPos">[in]片方の円の位置</param>
	/// <param name="pBPos">[in]もう片方の円の位置</param>
	/// <param name="aRadius">片方の円の半径</param>
	/// <param name="bRadius">もう片方の円の位置</param>
	/// <returns>衝突していればtrue</returns>
	inline bool CollidesCircles(const D3DXVECTOR3* pACenter, const D3DXVECTOR3* pBCenter, float aRadius, float bRadius) const
	{
		return m_pCollision->CollidesCircles(pACenter, pBCenter, aRadius, bRadius);
	}

	/// <summary>
	/// 円と円の衝突判定を返す、衝突していればtrue
	/// </summary>
	/// <param name="pA">[in]片方の円の頂点情報配列の先頭アドレス</param>
	/// <param name="pB">[in]もう片方の円の頂点情報配列の先頭アドレス</param>
	/// <returns>衝突していればtrue</returns>
	inline bool CollidesCircles(const CustomVertex* pA, const CustomVertex* pB) const
	{
		return m_pCollision->CollidesCircles(pA, pB);
	}

	/// <summary>
	/// 矩形と矩形の衝突判定を返す、衝突していればtrue
	/// </summary>
	/// <param name="pA">[in]片方の矩形の頂点情報配列の先頭アドレス</param>
	/// <param name="pB">[in]もう片方の矩形の頂点情報配列の先頭アドレス</param>
	/// <returns>衝突していればtrue</returns>
	inline bool CollidesRects(const CustomVertex* pA, const CustomVertex* pB) const
	{
		return m_pCollision->CollidesRects(pA, pB);
	}

	/// <summary>
	/// 音声ファイルの追加
	/// </summary>
	/// <param name="pFilePath">音声ファイルのパス</param>
	/// <param name="pKey">音声につけるキー</param>
	inline void AddSoundFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_pSound->AddFile(pFilePath, pKey);
	}

	/// <summary>
	/// 同時再生用音声ファイルの追加
	/// </summary>
	/// <param name="pFilePath">音声ファイルのパス</param>
	/// <param name="pKey">音声につけるキー</param>
	inline void AddSimultaneousSoundFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_pSound->AddSimultaneousFile(pFilePath, pKey);
	}

	/// <summary>
	/// 同時再生用音声の再生(ループなし)
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	inline void SimultaneousStartSoundOneShot(const TCHAR* pKey)
	{
		m_pSound->SimultaneousStartOneShot(pKey);
	}

	/// <summary>
	/// ループ再生させる
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	inline void StartSoundLoop(const TCHAR* pKey)
	{
		m_pSound->StartLoop(pKey);
	}

	/// <summary>
	/// 音声の再生(ループなし)
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	/// <returns></returns>
	inline void StartOneShot(const TCHAR* pKey)
	{
		m_pSound->StartOneShot(pKey);
	}

	/// <summary>
	/// 音声の一時停止
	/// </summary>
	/// <param name="pKey">一時停止したい音声のキー</param>
	inline void PauseSound(const TCHAR* pKey)
	{
		m_pSound->Pause(pKey);
	}

	/// <summary>
	/// 一時停止していた音声の再生
	/// </summary>
	/// <param name="pKey">再生させたい音声のキー</param>
	inline void ResumeSound(const TCHAR* pKey)
	{
		m_pSound->Resume(pKey);
	}

	/// <summary>
	/// 音声の停止
	/// 停止するのには少し時間がかかる
	/// </summary>
	/// <param name="pKey">停止したい音声のキー</param>
	inline void StopSound(const TCHAR* pKey)
	{
		m_pSound->Stop(pKey);
	}

	/// <summary>
	/// ボリュームの調整
	/// </summary>
	/// <param name="pKey">調整したい音声のキー</param>
	/// <param name="volume">
	/// 0~100までのボリューム
	/// デフォルトでは100
	/// </param>
	inline void SetSoundVolume(const TCHAR* pKey, int volume)
	{
		m_pSound->SetVolume(pKey, volume);
	}

	inline bool ConnectJoycon(Joycon::CONTROLLER_TYPE controllerType) const
	{
		return m_pJoyconManager->Connect(controllerType);
	}

	inline bool GetIsConnectJoycon(Joycon::CONTROLLER_TYPE controllerType) const
	{
		return m_pJoyconManager->GetJoycon(controllerType)->GetIsConnect();
	}

	inline void DisconnectJoycon(Joycon::CONTROLLER_TYPE controllerType) const
	{
		m_pJoyconManager->Disconnect(controllerType);
	}

	inline bool PushJoyconButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		return m_pJoyconManager->PushButton(controllerType, button);
	}

	inline bool ReleaseJoyconButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		return m_pJoyconManager->ReleaseButton(controllerType, button);
	}

	inline bool HoldJoyconButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		return m_pJoyconManager->HoldButton(controllerType, button);
	}

	inline bool NeutralJoyconButton(Joycon::CONTROLLER_TYPE controllerType, int button) const
	{
		return m_pJoyconManager->NeutralButton(controllerType, button);
	}

	inline bool PushJoyconAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->PushAnalogStick(controllerType, direction);
	}

	inline bool HoldJoyconAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->HoldAnalogStick(controllerType, direction);
	}

	inline bool ReleaseJoyconAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->ReleaseAnalogStick(controllerType, direction);
	}

	inline bool NeutralJoyconAnalogStick(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->NeutralAnalogStick(controllerType, direction);
	}

	inline bool InputGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->InputGyroSensor(controllerType, direction);
	}

	inline bool MoveGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->MoveGyroSensor(controllerType, direction);
	}

	inline bool StopGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->StopGyroSensor(controllerType, direction);
	}

	inline bool NeutralGyroSensor(Joycon::CONTROLLER_TYPE controllerType, int direction) const
	{
		return m_pJoyconManager->NeutralGyroSensor(controllerType, direction);
	}

	inline void JoyconRumble(Joycon::CONTROLLER_TYPE controllerType)
	{
		m_pJoyconManager->GetJoycon(controllerType)->SendRumble();
	}

	/// <summary>
	/// エフェクトの追加
	/// </summary>
	/// <param name="pEffect">追加したいエフェクトのポインタ</param>
	inline void AddEffect(Effect* pEffect)
	{
		m_pEffectManager->AddEffect(pEffect);
	}

	/// <summary>
	/// 全てのエフェクトの開放
	/// </summary>
	inline void AllRelease()
	{
		m_pEffectManager->AllRelease();
	}

 	/// <summary>
	/// FPSの設定を行う
	/// </summary>
	/// <param name="fPS">設定したい一秒間でのフレーム数</param>
	/// <remarks>設定していなかった場合60fps</remarks>
	inline void SetFPS(int fPS)
	{
		m_rTimerManager.SetFPS(fPS);
	}

	/// <summary>
	/// 一フレームにかかった時間(秒)を取得する
	/// </summary>
	/// <returns>経過時間(秒)</returns>
	inline float DeltaTime_s() const
	{
		return m_rTimerManager.DeltaTime_s();
	}

	/// <summary>
	/// タイマーの作成を行う
	/// </summary>
	/// <param name="pKey">生成するタイマーにつける識別キー</param>
	inline void CreateTimer(const TCHAR* pKey)
	{
		m_rTimerManager.Create(pKey);
	}

	/// <summary>
	/// 引数に渡されたキーのタイマーの開放
	/// </summary>
	/// <param name="pKey">開放したいタイマーのキー</param>
	inline void ReleaseTimer(const TCHAR* pKey)
	{
		m_rTimerManager.Release(pKey);
	}

	/// <summary>
	/// 引数に渡されたキーのタイマーが存在しているか
	/// </summary>
	/// <param name="pKey">調べたいタイマーの識別キー</param>
	/// <returns>存在していればtrue</returns>
	inline bool TimerExists(const TCHAR* pKey) const
	{
		return m_rTimerManager.Exists(pKey);
	}

	/// <summary>
	/// 時間の計測開始
	/// </summary>
	/// <param name="pKey">計測開始するタイマーのキー</param>
	inline void StartTimer(const TCHAR* pKey)
	{
		m_rTimerManager.Start(pKey);
	}

	/// <summary>
	/// 時間計測の一時停止
	/// </summary>
	/// <param name="pKey">一時停止するタイマーのキー</param>
	inline void PauseTimer(const TCHAR* pKey)
	{
		m_rTimerManager.Pause(pKey);
	}

	/// <summary>
	/// 時間計測のリスタート
	/// </summary>
	/// <param name="pKey">計測を再スタートさせるタイマーのキー</param>
	inline void RestartTimer(const TCHAR* pKey)
	{
		m_rTimerManager.Restart(pKey);
	}

	/// <summary>
	/// 時間計測の初期化し,計測開始時間を現在の開始時間にする
	/// </summary>
	/// <param name="pKey">初期化したいタイマーのキー</param>
	inline void ResetTimer(const TCHAR* pKey)
	{
		m_rTimerManager.Reset(pKey);
	}

	/// <summary>
	/// 計測時間を返す(秒)
	/// </summary>
	/// <param name="pKey">タイマーのキー</param>
	inline LONGLONG GetTime_s(const TCHAR* pKey)
	{
		return m_rTimerManager.GetTime_s(pKey);
	}

	/// <summary>
	/// 計測時間を返す(ミリ秒)
	/// </summary>
	/// <param name="pKey">タイマーのキー</param>
	inline LONGLONG GetTime_ms(const TCHAR* pKey)
	{
		return m_rTimerManager.GetTime_ms(pKey);
	}

	/// <summary>
	/// 計測時間を返す(マイクロ秒)
	/// </summary>
	/// <param name="pKey">タイマーのキー</param>
	inline LONGLONG GetTime_µs(const TCHAR* pKey)
	{
		return m_rTimerManager.GetTime_µs(pKey);
	}

	/// <summary>
	/// 現在計測が止まっているかを返す
	/// </summary>
	/// <param name="pKey">止まっているかを調べるタイマーのキー</param>
	/// <returns>止まっていればtrue</returns>
	inline bool IsTimerRunning(const TCHAR* pKey)
	{
		return m_rTimerManager.IsRunning(pKey);
	}

	////////////////
	/// XINPUT
	////////////////

	/// <summary>
	/// PADの接続、入力状態の確認
	/// </summary>
	/// <seealso cref="GetControl"/>
	/// <seealso cref="BottonCheck"/>
	void DeviceUpdate()
	{
		return m_pXinputManager->DeviceUpdate();
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの入力取得
	/// </summary>
	/// <param name="index">取得したいボタンの配列番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>PADSTATEの値</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetButton(Xinput::ButtonIndex index, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetButton(index, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドのトリガーの入力取得
	/// </summary>
	/// <param name="Trigger">トリガーの左右認識番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>0～255の値、押してなければ0</returns>
	/// <seealso cref="Xinput::AnalogTrigger"/>
	int GetAnalogTrigger(Xinput::AnalogTrigger Trigger, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogTrigger(Trigger, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetAnalogL(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogL(AnalogState, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾いていればTrue、そうでなければFalse</returns>
	/// <seealso cref="Xinput::Analog"/>
	bool GetAnalogR(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogR(AnalogState, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetAnalogLValue(Xinput::AnalogAxis AnalogState, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogLValue(AnalogState, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの右アナログスティック入力取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
	/// <seealso cref="Xinput::Analog"/>
	int GetAnalogRValue(Xinput::AnalogAxis AnalogState, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogRValue(AnalogState, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetAnalogLState(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogLState(AnalogState, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
	/// </summary>
	/// <param name="AnalogState">スティックの方向け先番号</param>
	/// <param name="num">コントローラ番号</param>
	/// <returns>方向け状態</returns>
	/// <seealso cref="Xinput::Analog"/>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetAnalogRState(Xinput::Analog AnalogState, Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetAnalogRState(AnalogState, num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの右トリガー入力状態取得
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerRState(Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetTriggerRState(num);
	}

	/// <summary>
	/// XinputDeviceでゲームパッドの左トリガー入力状態取得
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <returns>押下状態</returns>
	/// <seealso cref="Xinput::PADSTATE"/>
	Xinput::PADSTATE GetTriggerLState(Xinput::PLAYER_NUM num)
	{
		return m_pXinputManager->GetTriggerLState(num);
	}

	/// <summary>
	/// 左右のバイブレーションモーターを動作させる
	/// </summary>
	/// <param name="num">コントローラ番号</param>
	/// <param name="LeftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <param name="RightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
	/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
	void RunVibration(Xinput::PLAYER_NUM num, unsigned int LeftValue = 0, unsigned int RightValue = 0)
	{
		return m_pXinputManager->RunVibration(num, LeftValue, RightValue);
	}

private:
	GameLib() 
	{
		if (!m_pEffectManager)  m_pEffectManager = new EffectManager(static_cast<IGameLibRenderer*>(this));
	}

	static Wnd* m_pWnd;

	static DX* m_pDX;

	static Collision* m_pCollision;

	static Board3D* m_pBoard3D;

	static Sound* m_pSound;

	static JoyconManager* m_pJoyconManager;

	static EffectManager* m_pEffectManager;

	static XinputManager* m_pXinputManager;

	TimerManager& m_rTimerManager = TimerManager::GetInstance();
};

#endif //! GAME_LIB_H
