/**
* @file DX3D.h
* @brief 描画関係クラスのFacadeのヘッダ
*/

#ifndef DX3D_H
#define DX3D_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "D3DPP/D3DPP.h"
#include "ColorBlender/ColorBlender.h"
#include "Light/Light.h"
#include "TexStorage/TexStorage.h"
#include "Camera/Camera.h"
#include "CustomVertexEditor/CustomVertexEditor.h"
#include "Renderer/Renderer.h"
#include "FbxStorage/FbxStorage.h"
#include "FontStorage/FontStorage.h"
#include "Wnd/Data/RectSize.h"
#include "CustomVertex.h"
#include "VerticesParam.h"

/**
* @brief 描画関係クラスのFacade
*/
class DX3D
{
public:
	DX3D(HWND hWnd, RectSize wndSize, LPDIRECT3D9 pD3D);
	~DX3D()
	{
		delete m_pFbxStorage;
		delete m_pRenderer;
		delete m_pCustomVertex;
		delete m_pCamera;
		delete m_pTexStorage;
		delete m_pLight;
		delete m_pColorBlender;
		delete m_D3DPP;
		delete m_pFont;
		m_pDX3DDev->Release();
	}

	/**
	* @brief 描画の削除及び描画の開始宣言,メッセージループの始まりで呼ぶ
	*/
	VOID PrepareRendering() const;

	/**
	* @brief 描画の終了宣言及びバックバッファの入れ替え,メッセージループの終わりで呼ぶ
	*/
	VOID CleanUpRendering() const;
	
	/**
	* @brief ウィンドウモードの切替,3Dデバイスがロストする危険性がある
	*/
	VOID ToggleWndMode();

	/**
	* @brief 色の合成を通常合成に変更する デフォルトでは通常合成になっている
	*/
	inline VOID DefaultBlendMode() const
	{
		m_pColorBlender->DefaultBlendMode();
	}

	/**
	* @brief 色の合成を加算合成に変更する
	*/
	inline VOID AddtionBlendMode() const
	{
		m_pColorBlender->AddtionBlendMode();
	}

	/**
	* @brief デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline VOID DefaultColorBlending() const
	{
		m_pColorBlender->DefaultColorBlending();
	}

	/**
	* @brief 引数のライト構造体のデータを用いてライトを作成しそれを使う
	* @param light ライト構造体 phi等にも値を入れる必要があるときがある
	* @param index 作成するライトに振り分ける識別番号
	*/
	inline VOID SetLight(const D3DLIGHT9& rLight, DWORD index) const
	{
		m_pLight->SetLight(rLight, index);
	}

	/**
	* @brief SetLightで使用しているライトをonにする,SetLightをしたときに自動で呼ばれる
	* @param onにするライトに振り分けられた識別番号
	*/
	inline VOID OnLight(DWORD index) const
	{
		m_pLight->OnLight(index);
	}

	/**
	* @brief SetLightで使用しているライトをoffにする
	* @param offにするライトに振り分けられた識別番号
	*/
	inline VOID OffLight(DWORD index) const
	{
		m_pLight->OffLight(index);
	}

	/**
	* @brief ライティングを有効にする
	*/
	inline VOID EnableLighting() const
	{
		m_pLight->EnableLighting();
	}

	/**
	* @brief ライティングを無効にする ライトをすべて無効にする
	*/
	inline VOID DisableLighting() const
	{
		m_pLight->DisableLighting();
	}

	/**
	* @brief 環境光の強さを変更する 呼ばれていない場合環境光は使われない
	* @param aRGB 環境光の強さ 明るい色のほうが強くなる
	*/
	inline VOID ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_pLight->ChangeAmbientIntensity(aRGB);
	}

	/**
	* @brief 反射光を有効にする
	*/
	inline VOID EnableSpecular() const
	{
		m_pLight->EnableSpecular();
	}

	/**
	* @brief 反射光を無効にする
	*/
	inline VOID DisaableSpecular() const
	{
		m_pLight->DisaableSpecular();
	}

	/**
	* @brief デフォルトのライティングを使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline VOID DefaultLighting() const
	{
		m_pLight->DefaultLighting();
	}

	/**
	* @brief テクスチャを作成する
	* @param pTexKey テクスチャにつける名前のポインタ キー 連想配列
	* @param pTexPath 画像のパスのポインタ
	*/
	inline VOID CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		m_pTexStorage->CreateTex(pTexKey, pTexPath);
	}

	/**
	* @brief 全てのテクスチャの開放
	*/
	inline VOID AllTexRelease()
	{
		m_pTexStorage->AllRelease();
	}

	/// <summary>
	/// 指定したテクスチャの開放を行う
	/// </summary>
	/// <param name="pTexKey">[in]開放したいテクスチャのパス</param>
	inline VOID ReleaseTex(const TCHAR* pTexKey)
	{
		m_pTexStorage->Release(pTexKey);
	}

	/**
	* @brief テクスチャを取得する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return テクスチャのポインタ
	*/
	inline const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey) const
	{
		return m_pTexStorage->GetTex(pTexKey);
	}
	/**
	* @brief テクスチャが生成されているか判断する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return 存在していたらtrue
	*/
	inline const bool TexExists(const TCHAR* pTexKey) const
	{
		return m_pTexStorage->Exists(pTexKey);
	}

	/**
	* @brief 現在のカメラの位置を取得する
	* @param[out] pCameraPos カメラ位置を入れる
	*/
	inline VOID GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		m_pCamera->GetCameraPos(pCameraPos);
	}

	/**
	* @brief 現在のカメラの位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline VOID SetCameraPos(float x, float y, float z)
	{
		m_pCamera->SetCameraPos(x, y, z);
	}

	inline VOID SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_pCamera->SetCameraPos(rCameraPos);
	}

	/**
	* @brief 現在のカメラの注視点を取得する
	* @param[out] pEyePoint カメラの注視点を入れる
	*/
	inline VOID GetCameraEyePt(D3DXVECTOR3* pEyePoint) const
	{
		m_pCamera->GetCameraPos(pEyePoint);
	}

	/**
	* @brief 現在のカメラの注視点位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline VOID SetCameraEyePt(float x, float y, float z)
	{
		m_pCamera->SetEyePt(x, y, z);
	}

	inline VOID SetCameraEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_pCamera->SetEyePt(rEyePt);
	}

	/**
	* @brief カメラのビュー行列を取得する
	* @param[out] pView ビュー行列を入れる
	*/
	inline VOID GetView(D3DXMATRIX* pView) const
	{
		m_pCamera->GetView(pView);
	}

	/**
	* @brief カメラのプロジェクション行列を取得する
	* @param[out] pProjrction プロジェクション行列を入れる
	*/
	inline VOID GetProjection(D3DXMATRIX* pProjrction) const
	{
		m_pCamera->GetProjection(pProjrction);
	}

	/**
	* @brief カメラを適用させる
	*/
	inline VOID SetCameraTransform()
	{
		m_pCamera->SetTransform();
	}

	/**
	* @brief 引数の行列をビルボード化する、
	* 回転行列なのでかけ合わせる順番は回転行列をかけ合わせるとき
	* @param[in,out] pWorld ビルボード化する行列のポインタ
	*/
	inline VOID TransBillBoard(D3DXMATRIX* pWorld) const
	{
		m_pCamera->TransBillBoard(pWorld);
	}

	/// <summary>
	/// 引数のワールド座標をスクリーン座標に直した値を返す
	/// </summary>
	/// <param name="screenPos">[in]ワールド座標に直したいスクリーン座標</param>
	/// <returns>引数をワールド座標に直した値</returns>
	inline D3DXVECTOR3 TransScreen(const D3DXVECTOR3& Pos)
	{
		return m_pCamera->TransScreen(Pos);
	}

	/// <summary>
	/// 引数のスクリーン座標をワールド座標に直した値を返す
	/// </summary>
	/// <param name="worldPos">[in]スクリーン座標に直したいワールド座標</param>
	/// <returns>引数をスクリーン座標に直した値</returns>
	inline D3DXVECTOR3 TransWorld(const D3DXVECTOR3& Pos)
	{
		return m_pCamera->TransWorld(Pos);
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
		m_pCustomVertex->RotateXYZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief x軸で回転させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param 度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	*/
	inline VOID RotateRectX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pCustomVertex->RotateX(pCustomVertices, deg, relativeRotateCenter);
	}

	inline VOID RotateRectY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pCustomVertex->RotateY(pCustomVertices, deg, relativeRotateCenter);
	}

	inline VOID RotateRectZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pCustomVertex->RotateZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief 矩形を拡縮させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param scaleRate 拡縮率
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	inline VOID RescaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const
	{
		m_pCustomVertex->Rescale(pCustomVertices, scaleRate);
	}

	/**
	* @brief 矩形を移動させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param movement 移動量
	*/
	inline VOID MoveRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const
	{
		m_pCustomVertex->Move(pCustomVertices, movement);
	}

	/**
	* @brief 矩形を引数の位置に再配置させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param pos 矩形を移動させる座標
	*/
	inline VOID LocaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const
	{
		m_pCustomVertex->Locale(pCustomVertices, pos);
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
		m_pCustomVertex->SetTexUV(pCustomVertices, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param aRGB アルファ値入りのカラーコード ARGB
	*/
	inline VOID SetRectARGB(CustomVertex *pCustomVertices, DWORD aRGB) const
	{
		m_pCustomVertex->SetARGB(pCustomVertices, aRGB);
	}

	/// <summary>
	/// 矩形を上から下にグラデーションさせる
	/// </summary>
	/// <param name="pCustomVertices">[out]グラデーションさせたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="topARGB">上の色</param>
	/// <param name="bottomARGB">下の色</param>
	inline VOID SetTopBottomARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pCustomVertex->SetTopBottomARGB(pCustomVertices, topARGB, bottomARGB);
	}

	inline VOID SetLeftRightARGB(CustomVertex *pCustomVertices, DWORD leftARGB, DWORD rightARGB) const
	{
		m_pCustomVertex->SetLeftRightARGB(pCustomVertices, leftARGB, rightARGB);
	}

	inline VOID SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pCustomVertex->SetObliqueToBottomRightARGB(pCustomVertices, topARGB, bottomARGB);
	}

	inline VOID SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pCustomVertex->SetObliqueToBottomLeftARGB(pCustomVertices, topARGB, bottomARGB);
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
		m_pCustomVertex->Flash(pVertices, pFrameCnt, flashFlameMax, alphaMax, alphaMin);
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
		m_pCustomVertex->Create(pCustomVertices, center, halfScale, aRGB, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief 頂点データ構造体を引数の値から作成する 回転も行う
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param verticesParam オブジェクトの状態構造体
	*/
	inline VOID CreateRect(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const
	{
		m_pCustomVertex->Create(pCustomVertices, verticesParam);
	}

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline VOID Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pRenderer->Render(rFBXModel, rWorld, pTexture);
	}

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	inline VOID Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pRenderer->Render(pCustomVertices, pTexture);
	}

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline VOID Render(const Vertex3D* pVertex3D, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr)
	{
		m_pRenderer->Render(pVertex3D, rWorld, pTexture);
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
		m_pRenderer->Render(topLeft, pText, format, pFont, color);
	}

	/// <summary>
	/// 矩形の描画を行う
	/// </summary>
	/// <param name="verticesParam">頂点情報配列を作成するためのデータ</param>
	/// <param name="pTexture">矩形に張り付けるテクスチャのポインタ</param>
	inline VOID Render(const VerticesParam& verticesParam, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		CustomVertex vertices[CustomVertex::m_RECT_VERTICES_NUM];

		m_pCustomVertex->Create(vertices, verticesParam);

		m_pRenderer->Render(vertices, pTexture);
	}

	/// <summary>
	/// FBXオブジェクトの作成を行う
	/// </summary>
	/// <param name="pKey">[in]作成するオブジェクトにつけるキー</param>
	/// <param name="pFilePath">[in]作成するオブジェクトのパス</param>
	inline VOID CreateFbx(const TCHAR* pKey, const CHAR* pFilePath)
	{
		m_pFbxStorage->CreateFbx(pKey, pFilePath);
	}

	/// <summary>
	/// FBXオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">[in]取得したいオブジェクトのキー</param>
	/// <returns>FBXオブジェクトクラスの参照</returns>
	inline FbxRelated& GetFbx(const TCHAR* pKey)
	{
		return m_pFbxStorage->GetFbx(pKey);
	}

	/// <summary>
	/// フォントの全開放
	/// </summary>
	inline VOID AllFontRelease()
	{
		m_pFont->AllRelease();
	}

	/// <summary>
	/// 指定したフォントの開放
	/// </summary>
	/// <param name="pFontKey">開放したいフォントのキー</param>
	inline VOID ReleaseFont(const TCHAR* pFontKey)
	{
		m_pFont->Release(pFontKey);
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
		m_pFont->Create(pKey, scale, pFontName, thickness);
	}

	/// <summary>
	/// 文字が存在しているかを判別する
	/// </summary>
	/// <param name="pKey">判別したいフォントのキー</param>
	/// <returns>存在していればtrue</returns>
	inline bool FontExists(const TCHAR* pKey)
	{
		return m_pFont->Exists(pKey);
	}

	/// <summary>
	/// フォントオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">取得したいフォントのキー</param>
	/// <returns>フォントオブジェクトの参照</returns>
	inline const LPD3DXFONT GetFont(const TCHAR* pKey)
	{
		return m_pFont->GetFont(pKey);
	}

private:
	/// <summary>
	/// 先にDXクラスを生成しなければいけない
	/// </summary>
	VOID Create(LPDIRECT3D9 pD3D);

	/// <summary>
	/// 先に引数をFAILEDマクロで調べた後呼ぶ 現在中身はほぼ空
	/// </summary>
	VOID OnFailedChangeWndMode(HRESULT resetRetVal);

	/// <summary>
	/// 描画する距離の初期化を行う
	/// </summary>
	VOID InitViewPort();

	const HWND m_HWND = nullptr;

	LPDIRECT3DDEVICE9 m_pDX3DDev = nullptr;

	D3DPP* m_D3DPP = nullptr;

	ColorBlender* m_pColorBlender = nullptr;

	Light* m_pLight = nullptr;

	TexStorage* m_pTexStorage = nullptr;

	Camera* m_pCamera = nullptr;

	CustomVertexEditor* m_pCustomVertex = nullptr;

	Renderer* m_pRenderer = nullptr;

	FbxStorage* m_pFbxStorage = nullptr;

	FontStorage* m_pFont = nullptr;
};

#endif //! DX3D_H
