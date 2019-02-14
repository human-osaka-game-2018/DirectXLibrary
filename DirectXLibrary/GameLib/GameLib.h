/**
* @file GameLib.h
* @brief 汎用クラスのFacadeのヘッダ
* @author Harutaka-Tsujino
*/

#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../Class/Singleton/Singleton.h"
#include "Wnd\Wnd.h"
#include "DX\DX.h"
#include "DX\DX3D\CustomVertexEditor\Data\CustomVertex.h"
#include "DX\DX3D\CustomVertexEditor\Data\VerticesParam.h"
#include "Timer\Timer.h"
#include "Collision\Collision.h"
#include "3DBoard\3DBoard.h"
#include "Sound\Sound.h"
#include "JoyconManager\JoyconManager.h"

template<typename T>
VOID SafeRelease(T** ppType)
{
	delete (*ppType);
	*ppType = nullptr;
}

/**
* @brief 汎用クラスのFacade,ウィンドウ生成やDX関係の初期化も行う
*/
class GameLib :public Singleton<GameLib>
{
public:
	friend class Singleton<GameLib>;

	~GameLib()
	{
		delete m_pSound;
		delete m_pBoard3D;
		delete m_pCollision;
		delete m_pTimer;
		delete m_pDX;
		delete m_pWnd;
		delete m_pJoyconManager;
	}

	/**
	* @brief ウィンドウを生成しDX関係を初期化する,一番初めにこれを呼ぶ
	* @param hInst インスタンスのハンドル
	* @param pAppName アプリケーションの名前のポインタ
	*/
	inline static VOID Create(const HINSTANCE hInst, const TCHAR* pAppName)
	{
		if (!m_pWnd)			m_pWnd = new Wnd(hInst, pAppName);
		if (!m_pDX)				m_pDX = new DX(m_pWnd->GetHWND(), m_pWnd->GetWndSize());
		if (!m_pTimer)			m_pTimer = new Timer();
		if (!m_pCollision)		m_pCollision = new Collision();
		if (!m_pSound)			m_pSound = new Sound();
		if (!m_pBoard3D)		m_pBoard3D = new Board3D();
		if (!m_pJoyconManager)	m_pJoyconManager = new JoyconManager();

		GetInstance();
	}

	/**
	* @brief メッセージループを作成し引数で与えられた関数を60fpsで回す
	* @param メッセージループで回す関数のポインタ
	*/
	VOID RunFunc(VOID(*pMainFunc)());

	/**
	* @brief クライアント領域をm_WND_SIZEと同じにする
	*/
	inline VOID ResizeWnd() const
	{
		m_pWnd->ResizeWnd();
	}

	/**
	* @brief ウィンドウモードの切替,3Dデバイスがロストする危険性がある
	*/
	VOID ToggleWndMode()
	{
		m_pDX->ToggleWndMode();
	}

	/**
	* @brief 色の合成を通常合成に変更する デフォルトでは通常合成になっている
	*/
	inline VOID DefaultBlendMode() const
	{
		m_pDX->DefaultBlendMode();
	}

	/**
	* @brief 色の合成を加算合成に変更する
	*/
	inline VOID AddtionBlendMode() const
	{
		m_pDX->AddtionBlendMode();
	}

	/**
	* @brief デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline VOID DefaultColorBlending() const
	{
		m_pDX->DefaultColorBlending();
	}

	/**
	* @brief 引数のライト構造体のデータを用いてライトを作成しそれを使う
	* @param light ライト構造体 phi等にも値を入れる必要があるときがある
	* @param index 作成するライトに振り分ける識別番号
	*/
	inline VOID SetLight(const D3DLIGHT9& rLight, DWORD index) const
	{
		m_pDX->SetLight(rLight, index);
	}

	/**
	* @brief SetLightで使用しているライトをonにする,SetLightをしたときに自動で呼ばれる
	* @param onにするライトに振り分けられた識別番号
	*/
	inline VOID OnLight(DWORD index) const
	{
		m_pDX->OnLight(index);
	}

	/**
	* @brief SetLightで使用しているライトをoffにする
	* @param offにするライトに振り分けられた識別番号
	*/
	inline VOID OffLight(DWORD index) const
	{
		m_pDX->OffLight(index);
	}

	/**
	* @brief ライティングを有効にする
	*/
	inline VOID EnableLighting() const
	{
		m_pDX->EnableLighting();
	}

	/**
	* @brief ライティングを無効にする ライトをすべて無効にする
	*/
	inline VOID DisableLighting() const
	{
		m_pDX->DisableLighting();
	}

	/**
	* @brief 環境光の強さを変更する 呼ばれていない場合環境光は使われない
	* @param aRGB 環境光の強さ 明るい色のほうが強くなる
	*/
	inline VOID ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_pDX->ChangeAmbientIntensity(aRGB);
	}

	/**
	* @brief 反射光を有効にする
	*/
	inline VOID EnableSpecular() const
	{
		m_pDX->EnableSpecular();
	}

	/**
	* @brief 反射光を無効にする
	*/
	inline VOID DisaableSpecular() const
	{
		m_pDX->DisaableSpecular();
	}

	/**
	* @brief デフォルトのライティングを使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline VOID DefaultLighting() const
	{
		m_pDX->DefaultLighting();
	}

	/**
	* @brief テクスチャを作成する
	* @param pTexKey テクスチャにつける名前のポインタ キー 連想配列
	* @param pTexPath 画像のパスのポインタ
	*/
	inline VOID CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		m_pDX->CreateTex(pTexKey, pTexPath);
	}

	/**
	* @brief 全てのテクスチャの開放
	*/
	inline VOID AllTexRelease()
	{
		m_pDX->AllTexRelease();
	}

	/// <summary>
	/// 指定したテクスチャの開放を行う
	/// </summary>
	/// <param name="pTexKey">[in]開放したいテクスチャのパス</param>
	inline VOID ReleaseTex(const TCHAR* pTexKey)
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
	inline VOID GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		m_pDX->GetCameraPos(pCameraPos);
	}

	/**
	* @brief 現在のカメラの位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline VOID SetCameraPos(float x, float y, float z)
	{
		m_pDX->SetCameraPos(x, y, z);
	}

	inline VOID SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_pDX->SetCameraPos(rCameraPos);
	}

	/**
	* @brief 現在のカメラの注視点を取得する
	* @param[out] pEyePoint カメラの注視点を入れる
	*/
	inline VOID GetCameraEyePt(D3DXVECTOR3* pEyePoint) const
	{
		m_pDX->GetCameraPos(pEyePoint);
	}

	/**
	* @brief 現在のカメラの注視点位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline VOID SetCameraEyePt(float x, float y, float z)
	{
		m_pDX->SetCameraEyePt(x, y, z);
	}

	inline VOID SetCameraEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_pDX->SetCameraEyePt(rEyePt);
	}

	/**
	* @brief カメラのビュー行列を取得する
	* @param[out] pView ビュー行列を入れる
	*/
	inline VOID GetView(D3DXMATRIX* pView) const
	{
		m_pDX->GetView(pView);
	}

	/**
	* @brief カメラのプロジェクション行列を取得する
	* @param[out] pProjrction プロジェクション行列を入れる
	*/
	inline VOID GetProjection(D3DXMATRIX* pProjrction) const
	{
		m_pDX->GetProjection(pProjrction);
	}

	/**
	* @brief カメラを適用させる
	*/
	inline VOID SetCameraTransform()
	{
		m_pDX->SetCameraTransform();
	}

	/**
	* @brief 引数の行列をビルボード化する、
	* 回転行列なのでかけ合わせる順番は回転行列をかけ合わせるとき
	* @param[in,out] pWorld ビルボード化する行列のポインタ
	*/
	inline VOID TransBillBoard(D3DXMATRIX* pWorld) const
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
	inline VOID RotateRectXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3& deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectXYZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief x軸で回転させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param 度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	*/
	inline VOID RotateRectX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectX(pCustomVertices, deg, relativeRotateCenter);
	}

	inline VOID RotateRectY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectY(pCustomVertices, deg, relativeRotateCenter);
	}

	inline VOID RotateRectZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX->RotateRectZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief 矩形を拡縮させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param scaleRate 拡縮率
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	inline VOID RescaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const
	{
		m_pDX->RescaleRect(pCustomVertices, scaleRate);
	}

	/**
	* @brief 矩形を移動させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param movement 移動量
	*/
	inline VOID MoveRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const
	{
		m_pDX->MoveRect(pCustomVertices, movement);
	}

	/**
	* @brief 矩形を引数の位置に再配置させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param pos 矩形を移動させる座標
	*/
	inline VOID LocaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const
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
	inline VOID SetRectTexUV(CustomVertex* pCustomVertices,
		float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const
	{
		m_pDX->SetRectTexUV(pCustomVertices, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param aRGB アルファ値入りのカラーコード ARGB
	*/
	inline VOID SetRectARGB(CustomVertex *pCustomVertices, DWORD aRGB) const
	{
		m_pDX->SetRectARGB(pCustomVertices, aRGB);
	}

	/// <summary>
	/// 矩形を上から下にグラデーションさせる
	/// </summary>
	/// <param name="pCustomVertices">[out]グラデーションさせたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="topARGB">上の色</param>
	/// <param name="bottomARGB">下の色</param>
	inline VOID SetTopBottomARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX->SetTopBottomARGB(pCustomVertices, topARGB, bottomARGB);
	}

	inline VOID SetLeftRightARGB(CustomVertex *pCustomVertices, DWORD leftARGB, DWORD rightARGB) const
	{
		m_pDX->SetLeftRightARGB(pCustomVertices, leftARGB, rightARGB);
	}

	inline VOID SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX->SetObliqueToBottomRightARGB(pCustomVertices, topARGB, bottomARGB);
	}

	inline VOID SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX->SetObliqueToBottomLeftARGB(pCustomVertices, topARGB, bottomARGB);
	}

	/// <summary>
	/// 矩形を点滅させる
	/// </summary>
	/// <param name="pVertices">[out]点滅させたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="pFrameCnt">
	/// [in,out]点滅の強度を決めるためのカウント
	/// 関数内で自動で増減させるのでstaticかつ関数外で値を変えてはいけない
	/// </param>
	/// <param name="flashFlameMax">何フレームで一周期を終えるか</param>
	/// <param name="alphaMax">アルファ値の最大値</param>
	/// <param name="alphaMin">アルファ値の最小値</param>
	inline VOID FlashRect(CustomVertex* pVertices, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0)
	{
		m_pDX->FlashRect(pVertices, pFrameCnt, flashFlameMax, alphaMax, alphaMin);
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
	inline VOID CreateRect(CustomVertex *pCustomVertices, const D3DXVECTOR3& center, const D3DXVECTOR3& halfScale,
		DWORD aRGB = 0xFFFFFFFF, float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const
	{
		m_pDX->CreateRect(pCustomVertices, center, halfScale, aRGB, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief 頂点データ構造体を引数の値から作成する 回転も行う
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param verticesParam オブジェクトの状態構造体
	*/
	inline VOID CreateRect(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const
	{
		m_pDX->CreateRect(pCustomVertices, verticesParam);
	}

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline VOID Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(rFBXModel, rWorld, pTexture);
	}

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	inline VOID Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(pCustomVertices, pTexture);
	}

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline VOID Render(const Vertex3D* pVertex3D, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr)
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
	inline VOID Render(const D3DXVECTOR2& topLeft, const TCHAR* pText, UINT format, LPD3DXFONT pFont, DWORD color)
	{
		m_pDX->Render(topLeft, pText, format, pFont, color);
	}

	/// <summary>
	/// 矩形の描画を行う
	/// </summary>
	/// <param name="verticesParam">頂点情報配列を作成するためのデータ</param>
	/// <param name="pTexture">矩形に張り付けるテクスチャのポインタ</param>
	inline VOID Render(const VerticesParam& verticesParam, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX->Render(verticesParam, pTexture);
	}

	/// <summary>
	/// FBXオブジェクトの作成を行う
	/// </summary>
	/// <param name="pKey">[in]作成するオブジェクトにつけるキー</param>
	/// <param name="pFilePath">[in]作成するオブジェクトのパス</param>
	inline VOID CreateFbx(const TCHAR* pKey, const CHAR* pFilePath)
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
	inline VOID AllFontRelease()
	{
		m_pDX->AllFontRelease();
	}

	/// <summary>
	/// 指定したフォントの開放
	/// </summary>
	/// <param name="pFontKey">開放したいフォントのキー</param>
	inline VOID ReleaseFont(const TCHAR* pFontKey)
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
	inline VOID CreateFont(const TCHAR* pKey, D3DXVECTOR2 scale, const TCHAR* pFontName, UINT thickness = 0)
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
	inline VOID CursorPos(POINT* pPos) const
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

	inline VOID SetStartTime()
	{
		m_pTimer->Start();
	}

	inline VOID SetEndTime()
	{
		m_pTimer->End();
	}

	inline VOID ResetTime()
	{
		m_pTimer->Reset();
	}

	inline VOID StopTime()
	{
		m_pTimer->Stop();
	}

	inline VOID RestartTime()
	{
		m_pTimer->Restart();
	}

	inline LONGLONG GetSecond()
	{
		return m_pTimer->GetSecond();
	}

	inline LONGLONG GetMilliSecond()
	{
		return m_pTimer->GetMilliSecond();
	}

	inline LONGLONG GetMicroSecond()
	{
		return m_pTimer->GetMicroSecond();
	}

	inline bool GetTimeIsStoped()
	{
		return m_pTimer->GetIsStoped();
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
	inline VOID AddSoundFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_pSound->AddFile(pFilePath, pKey);
	}

	/// <summary>
	/// 同時再生用音声ファイルの追加
	/// </summary>
	/// <param name="pFilePath">音声ファイルのパス</param>
	/// <param name="pKey">音声につけるキー</param>
	inline VOID AddSimultaneousSoundFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_pSound->AddSimultaneousFile(pFilePath, pKey);
	}

	/// <summary>
	/// 同時再生用音声の再生(ループなし)
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	inline VOID SimultaneousStartSoundOneShot(const TCHAR* pKey)
	{
		m_pSound->SimultaneousStartOneShot(pKey);
	}

	/// <summary>
	/// ループ再生させる
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	inline VOID StartSoundLoop(const TCHAR* pKey)
	{
		m_pSound->StartLoop(pKey);
	}

	/// <summary>
	/// 音声の再生(ループなし)
	/// </summary>
	/// <param name="pKey">再生したい音声のキー</param>
	/// <returns></returns>
	inline VOID StartOneShot(const TCHAR* pKey)
	{
		m_pSound->StartOneShot(pKey);
	}

	/// <summary>
	/// 音声の一時停止
	/// </summary>
	/// <param name="pKey">一時停止したい音声のキー</param>
	inline VOID PauseSound(const TCHAR* pKey)
	{
		m_pSound->Pause(pKey);
	}

	/// <summary>
	/// 一時停止していた音声の再生
	/// </summary>
	/// <param name="pKey">再生させたい音声のキー</param>
	inline VOID ResumeSound(const TCHAR* pKey)
	{
		m_pSound->Resume(pKey);
	}

	/// <summary>
	/// 音声の停止
	/// 停止するのには少し時間がかかる
	/// </summary>
	/// <param name="pKey">停止したい音声のキー</param>
	inline VOID StopSound(const TCHAR* pKey)
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
	inline VOID SetSoundVolume(const TCHAR* pKey, int volume)
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

	inline VOID DisconnectJoycon(Joycon::CONTROLLER_TYPE controllerType) const
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

	inline VOID JoyconRumble(Joycon::CONTROLLER_TYPE controllerType)
	{
		m_pJoyconManager->GetJoycon(controllerType)->SendRumble();
	}

private:
	GameLib() {};

	static Wnd* m_pWnd;

	static DX* m_pDX;

	static Timer* m_pTimer;

	static Collision* m_pCollision;

	static Board3D* m_pBoard3D;

	static Sound* m_pSound;

	static JoyconManager* m_pJoyconManager;
};

#endif //! GAME_LIB_H
