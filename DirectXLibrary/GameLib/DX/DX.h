/**
* @param DX.h
* @brief DX関係クラスのFacadeのヘッダ
*/

#ifndef DX_H
#define DX_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "Wnd/Data/RectSize.h"
#include "DX3D/DX3D.h"
#include "DXInput/DXInput.h"
#include "CustomVertex.h"
#include "VerticesParam.h"

/**
* @brief DX関係クラスのFacade
*/
class DX
{
public:
	DX(HWND hWnd, RectSize wndSize) :m_HWND(hWnd)
	{
		Create();

		m_pDX3D = new DX3D(m_HWND, wndSize, m_pD3D);

		m_pDXInput = new DXInput(m_HWND);
	}

	~DX()
	{
		delete m_pDX3D;
		delete m_pDXInput;
		m_pD3D->Release();
	}

	/**
	* @brief 描画の開始処理と入力状態の更新を行う,メッセージループの始まりで呼ぶ
	*/
	inline void PrepareMessageLoop() const
	{
		m_pDX3D->PrepareRendering();
		m_pDXInput->UpdataInputState();
	}

	/**
	* @brief 描画の終了処理と入力状態の保存を行う,メッセージループの終わりで呼ぶ
	*/
	inline void CleanUpMessageLoop() const
	{
		m_pDX3D->CleanUpRendering();
		m_pDXInput->StorePrevInputState();
	}

	/**
	* @brief ウィンドウモードの切替,3Dデバイスがロストする危険性がある
	*/
	void ToggleWndMode()
	{
		m_pDX3D->ToggleWndMode();
	}

	/**
	* @brief 色の合成を通常合成に変更する デフォルトでは通常合成になっている
	*/
	inline void DefaultBlendMode() const
	{
		m_pDX3D->DefaultBlendMode();
	}

	/**
	* @brief 色の合成を加算合成に変更する
	*/
	inline void AddtionBlendMode() const
	{
		m_pDX3D->AddtionBlendMode();
	}

	/**
	* @brief デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline void DefaultColorBlending() const
	{
		m_pDX3D->DefaultColorBlending();
	}

	/**
	* @brief 引数のライト構造体のデータを用いてライトを作成しそれを使う
	* @param light ライト構造体 phi等にも値を入れる必要があるときがある
	* @param index 作成するライトに振り分ける識別番号
	*/
	inline void SetLight(const D3DLIGHT9& rLight, DWORD index) const
	{
		m_pDX3D->SetLight(rLight, index);
	}

	/**
	* @brief SetLightで使用しているライトをonにする,SetLightをしたときに自動で呼ばれる
	* @param onにするライトに振り分けられた識別番号
	*/
	inline void OnLight(DWORD index) const
	{
		m_pDX3D->OnLight(index);
	}

	/**
	* @brief SetLightで使用しているライトをoffにする
	* @param offにするライトに振り分けられた識別番号
	*/
	inline void OffLight(DWORD index) const
	{
		m_pDX3D->OffLight(index);
	}

	/**
	* @brief ライティングを有効にする
	*/
	inline void EnableLighting() const
	{
		m_pDX3D->EnableLighting();
	}

	/**
	* @brief ライティングを無効にする ライトをすべて無効にする
	*/
	inline void DisableLighting() const
	{
		m_pDX3D->DisableLighting();
	}

	/**
	* @brief 環境光の強さを変更する 呼ばれていない場合環境光は使われない
	* @param aRGB 環境光の強さ 明るい色のほうが強くなる
	*/
	inline void ChangeAmbientIntensity(DWORD aRGB) const
	{
		m_pDX3D->ChangeAmbientIntensity(aRGB);
	}

	/**
	* @brief 反射光を有効にする
	*/
	inline void EnableSpecular() const
	{
		m_pDX3D->EnableSpecular();
	}

	/**
	* @brief 反射光を無効にする
	*/
	inline void DisaableSpecular() const
	{
		m_pDX3D->DisaableSpecular();
	}

	/**
	* @brief デフォルトのライティングを使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	inline void DefaultLighting() const
	{
		m_pDX3D->DefaultLighting();
	}

	/**
	* @brief テクスチャを作成する
	* @param pTexKey テクスチャにつける名前のポインタ キー 連想配列
	* @param pTexPath 画像のパスのポインタ
	*/
	inline void CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath)
	{
		m_pDX3D->CreateTex(pTexKey, pTexPath);
	}

	/**
	* @brief 全てのテクスチャの開放
	*/
	inline void AllTexRelease()
	{
		m_pDX3D->AllTexRelease();
	}

	/// <summary>
	/// 指定したテクスチャの開放を行う
	/// </summary>
	/// <param name="pTexKey">[in]開放したいテクスチャのパス</param>
	inline void ReleaseTex(const TCHAR* pTexKey)
	{
		m_pDX3D->ReleaseTex(pTexKey);
	}

	/**
	* @brief テクスチャを取得する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return テクスチャのポインタ
	*/
	inline const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey) const
	{
		return m_pDX3D->GetTex(pTexKey);
	}
	/**
	* @brief テクスチャが生成されているか判断する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return 存在していたらtrue
	*/
	inline const bool TexExists(const TCHAR* pTexKey) const
	{
		return m_pDX3D->TexExists(pTexKey);
	}

	/**
	* @brief 現在のカメラの位置を取得する
	* @param[out] pCameraPos カメラ位置を入れる
	*/
	inline void GetCameraPos(D3DXVECTOR3* pCameraPos) const
	{
		m_pDX3D->GetCameraPos(pCameraPos);
	}

	/**
	* @brief 現在のカメラの位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline void SetCameraPos(float x, float y, float z)
	{
		m_pDX3D->SetCameraPos(x, y, z);
	}

	inline void SetCameraPos(const D3DXVECTOR3& rCameraPos)
	{
		m_pDX3D->SetCameraPos(rCameraPos);
	}

	/**
	* @brief 現在のカメラの注視点を取得する
	* @param[out] pEyePoint カメラの注視点を入れる
	*/
	inline void GetCameraEyePt(D3DXVECTOR3* pEyePoint) const
	{
		m_pDX3D->GetCameraPos(pEyePoint);
	}

	/**
	* @brief 現在のカメラの注視点位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	inline void SetCameraEyePt(float x, float y, float z)
	{
		m_pDX3D->SetCameraEyePt(x, y, z);
	}

	inline void SetCameraEyePt(const D3DXVECTOR3& rEyePt)
	{
		m_pDX3D->SetCameraEyePt(rEyePt);
	}

	/**
	* @brief カメラのビュー行列を取得する
	* @param[out] pView ビュー行列を入れる
	*/
	inline void GetView(D3DXMATRIX* pView) const
	{
		m_pDX3D->GetView(pView);
	}

	/**
	* @brief カメラのプロジェクション行列を取得する
	* @param[out] pProjrction プロジェクション行列を入れる
	*/
	inline void GetProjection(D3DXMATRIX* pProjrction) const
	{
		m_pDX3D->GetProjection(pProjrction);
	}

	/**
	* @brief カメラを適用させる
	*/
	inline void SetCameraTransform()
	{
		m_pDX3D->SetCameraTransform();
	}

	/**
	* @brief 引数の行列をビルボード化する、
	* 回転行列なのでかけ合わせる順番は回転行列をかけ合わせるとき
	* @param[in,out] pWorld ビルボード化する行列のポインタ
	*/
	inline void TransBillBoard(D3DXMATRIX* pWorld) const
	{
		m_pDX3D->TransBillBoard(pWorld);
	}

	/// <summary>
	/// 引数のワールド座標をスクリーン座標に直した値を返す
	/// </summary>
	/// <param name="screenPos">[in]ワールド座標に直したいスクリーン座標</param>
	/// <returns>引数をワールド座標に直した値</returns>
	inline D3DXVECTOR3 TransScreen(const D3DXVECTOR3& Pos)
	{
		return m_pDX3D->TransScreen(Pos);
	}

	/// <summary>
	/// 引数のスクリーン座標をワールド座標に直した値を返す
	/// </summary>
	/// <param name="worldPos">[in]スクリーン座標に直したいワールド座標</param>
	/// <returns>引数をスクリーン座標に直した値</returns>
	inline D3DXVECTOR3 TransWorld(const D3DXVECTOR3& Pos)
	{
		return m_pDX3D->TransWorld(Pos);
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
		m_pDX3D->RotateRectXYZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief x軸で回転させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param 度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	*/
	inline void RotateRectX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX3D->RotateRectX(pCustomVertices, deg, relativeRotateCenter);
	}

	inline void RotateRectY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX3D->RotateRectY(pCustomVertices, deg, relativeRotateCenter);
	}

	inline void RotateRectZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		m_pDX3D->RotateRectZ(pCustomVertices, deg, relativeRotateCenter);
	}

	/**
	* @brief 矩形を拡縮させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param scaleRate 拡縮率
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	inline void RescaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const
	{
		m_pDX3D->RescaleRect(pCustomVertices, scaleRate);
	}

	/**
	* @brief 矩形を移動させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param movement 移動量
	*/
	inline void MoveRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const
	{
		m_pDX3D->MoveRect(pCustomVertices, movement);
	}

	/**
	* @brief 矩形を引数の位置に再配置させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param pos 矩形を移動させる座標
	*/
	inline void LocaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const
	{
		m_pDX3D->LocaleRect(pCustomVertices, pos);
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
		m_pDX3D->SetRectTexUV(pCustomVertices, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief 矩形の色を引数の色に変更する
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param aRGB アルファ値入りのカラーコード ARGB
	*/
	inline void SetRectARGB(CustomVertex *pCustomVertices, DWORD aRGB) const
	{
		m_pDX3D->SetRectARGB(pCustomVertices, aRGB);
	}

	/// <summary>
	/// 矩形を上から下にグラデーションさせる
	/// </summary>
	/// <param name="pCustomVertices">[out]グラデーションさせたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="topARGB">上の色</param>
	/// <param name="bottomARGB">下の色</param>
	inline void SetTopBottomARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX3D->SetTopBottomARGB(pCustomVertices, topARGB, bottomARGB);
	}

	inline void SetLeftRightARGB(CustomVertex *pCustomVertices, DWORD leftARGB, DWORD rightARGB) const
	{
		m_pDX3D->SetLeftRightARGB(pCustomVertices, leftARGB, rightARGB);
	}

	inline void SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX3D->SetObliqueToBottomRightARGB(pCustomVertices, topARGB, bottomARGB);
	}

	inline void SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const
	{
		m_pDX3D->SetObliqueToBottomLeftARGB(pCustomVertices, topARGB, bottomARGB);
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
	inline void FlashRect(CustomVertex* pVertices, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const
	{
		m_pDX3D->FlashRect(pVertices, pFrameCnt, flashFlameMax, alphaMax, alphaMin);
	}

	inline void FlashRect(VerticesParam* pVerticesParam, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const
	{
		m_pDX3D->FlashRect(pVerticesParam, pFrameCnt, flashFlameMax, alphaMax, alphaMin);
	}

	/// <summary>
	/// アルファ値のみを変更する
	/// </summary>
	/// <param name="pVerticesParam">矩形の頂点情報のデータ</param>
	/// <param name="alpha">変更したいアルファ値</param>
	void SetRectAlpha(VerticesParam* pVerticesParam, BYTE alpha) const
	{
		m_pDX3D->SetRectAlpha(pVerticesParam, alpha);
	}

	void SetRectAlpha(CustomVertex* pVertices, BYTE alpha) const
	{
		m_pDX3D->SetRectAlpha(pVertices, alpha);
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
		m_pDX3D->CreateRect(pCustomVertices, center, halfScale, aRGB, startTU, startTV, endTU, endTV);
	}

	/**
	* @brief 頂点データ構造体を引数の値から作成する 回転も行う
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param verticesParam オブジェクトの状態構造体
	*/
	inline void CreateRect(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const
	{
		m_pDX3D->CreateRect(pCustomVertices, verticesParam);
	}

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline void Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX3D->Render(rFBXModel, rWorld, pTexture);
	}

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	inline void Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX3D->Render(pCustomVertices, pTexture);
	}

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	inline void Render(const Vertex3D* pVertex3D, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr)
	{
		m_pDX3D->Render(pVertex3D, rWorld, pTexture);
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
		m_pDX3D->Render(topLeft, pText, format, pFont, color);
	}

	/// <summary>
	/// 矩形の描画を行う
	/// </summary>
	/// <param name="verticesParam">頂点情報配列を作成するためのデータ</param>
	/// <param name="pTexture">矩形に張り付けるテクスチャのポインタ</param>
	inline void Render(const VerticesParam& verticesParam, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const
	{
		m_pDX3D->Render(verticesParam, pTexture);
	}

	/// <summary>
	/// FBXオブジェクトの作成を行う
	/// </summary>
	/// <param name="pKey">[in]作成するオブジェクトにつけるキー</param>
	/// <param name="pFilePath">[in]作成するオブジェクトのパス</param>
	inline void CreateFbx(const TCHAR* pKey, const CHAR* pFilePath)
	{
		m_pDX3D->CreateFbx(pKey, pFilePath);
	}

	/// <summary>
	/// FBXオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">[in]取得したいオブジェクトのキー</param>
	/// <returns>FBXオブジェクトクラスの参照</returns>
	inline FbxRelated& GetFbx(const TCHAR* pKey)
	{
		return m_pDX3D->GetFbx(pKey);
	}

	/// <summary>
	/// フォントの全開放
	/// </summary>
	inline void AllFontRelease()
	{
		m_pDX3D->AllFontRelease();
	}

	/// <summary>
	/// 指定したフォントの開放
	/// </summary>
	/// <param name="pFontKey">開放したいフォントのキー</param>
	inline void ReleaseFont(const TCHAR* pFontKey)
	{
		m_pDX3D->ReleaseFont(pFontKey);
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
		m_pDX3D->CreateFont(pKey, scale, pFontName, thickness);
	}

	/// <summary>
	/// 文字が存在しているかを判別する
	/// </summary>
	/// <param name="pKey">判別したいフォントのキー</param>
	/// <returns>存在していればtrue</returns>
	inline bool FontExists(const TCHAR* pKey)
	{
		return m_pDX3D->FontExists(pKey);
	}

	/// <summary>
	/// フォントオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">取得したいフォントのキー</param>
	/// <returns>フォントオブジェクトの参照</returns>
	inline const LPD3DXFONT GetFont(const TCHAR* pKey)
	{
		return m_pDX3D->GetFont(pKey);
	}

	/// <summary>
	/// 引数に渡したボタンが押された瞬間か
	/// </summary>
	/// <param name="key">ボタンの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool MouseIsPressed(int key) const
	{
		return m_pDXInput->MouseIsPressed(key);
	}

	inline bool MouseIsHeld(int key) const
	{
		return m_pDXInput->MouseIsHeld(key);
	}

	inline bool MouseIsReleased(int key) const
	{
		return m_pDXInput->MouseIsReleased(key);
	}

	inline bool MouseIsNeutral(int key) const
	{
		return m_pDXInput->MouseIsNeutral(key);
	}

	/// <summary>
	/// 何かのボタンが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool MouseAnyKeyIsPressed() const
	{
		return m_pDXInput->MouseAnyKeyIsPressed();
	}

	/// <summary>
	/// カーソルの位置の取得
	/// </summary>
	/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
	inline void CursorPos(POINT* pPos) const
	{
		m_pDXInput->CursorPos(pPos);
	}

	/// <summary>
	/// 前フレームからどのくらいスクロールされたか
	/// </summary>
	/// <returns>スクロールされた量</returns>
	inline long MouseWheelScrollingFromPrev() const
	{
		return m_pDXInput->MouseWheelScrollingFromPrev();
	}

	/// <summary>
	/// 引数に渡したキーが押された瞬間か
	/// </summary>
	/// <param name="key">キーの列挙体</param>
	/// <returns>押された瞬間ならtrue</returns>
	inline bool KeyboardIsPressed(int key) const
	{
		return m_pDXInput->KeyboardIsPressed(key);
	}

	inline bool KeyboardIsHeld(int key) const
	{
		return m_pDXInput->KeyboardIsHeld(key);
	}

	inline bool KeyboardIsReleased(int key) const
	{
		return m_pDXInput->KeyboardIsReleased(key);
	}

	inline bool KeyboardIsNeutral(int key) const
	{
		return m_pDXInput->KeyboardIsNeutral(key);
	}

	/// <summary>
	/// 何かのキーが押された瞬間か
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	inline bool KeyboardAnyKeyIsPressed() const
	{
		return m_pDXInput->KeyboardAnyKeyIsPressed();
	}

private:
	/// <summary>
	/// 他DX機能の基盤となるので初めに生成する
	/// </summary>
	void Create();

	const HWND m_HWND = nullptr;

	LPDIRECT3D9 m_pD3D = nullptr;

	DX3D* m_pDX3D = nullptr;

	DXInput* m_pDXInput = nullptr;
};

#endif //! DX_H
