/// <filename>
/// IGameLibRenderer.h
/// </filename>
/// <summary>
/// GameLibの描画関連のインターフェイスのヘッダ
/// </summary>

#ifndef I_GAME_LIB_RENDERER_H
#define I_GAME_LIB_RENDERER_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "CustomVertex.h"
#include "VerticesParam.h"
#include "DX\DX3D\FbxStorage\FbxStorage.h"
#include "3DBoard\3DBoard.h"

/// <summary>
/// GameLibの描画関連のインターフェイス
/// </summary>
class IGameLibRenderer
{
public:
	/**
	* @brief 色の合成を通常合成に変更する デフォルトでは通常合成になっている
	*/
	virtual void DefaultBlendMode() const = 0;

	/**
	* @brief 色の合成を加算合成に変更する
	*/
	virtual void AddtionBlendMode() const = 0;

	/**
	* @brief デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	virtual void DefaultColorBlending() const = 0;

	/**
	* @brief 引数のライト構造体のデータを用いてライトを作成しそれを使う
	* @param light ライト構造体 phi等にも値を入れる必要があるときがある
	* @param index 作成するライトに振り分ける識別番号
	*/
	virtual void SetLight(const D3DLIGHT9& rLight, DWORD index) const = 0;

	/**
	* @brief SetLightで使用しているライトをonにする,SetLightをしたときに自動で呼ばれる
	* @param onにするライトに振り分けられた識別番号
	*/
	virtual void OnLight(DWORD index) const = 0;

	/**
	* @brief SetLightで使用しているライトをoffにする
	* @param offにするライトに振り分けられた識別番号
	*/
	virtual void OffLight(DWORD index) const = 0;

	/**
	* @brief ライティングを有効にする
	*/
	virtual void EnableLighting() const = 0;

	/**
	* @brief ライティングを無効にする ライトをすべて無効にする
	*/
	virtual void DisableLighting() const = 0;

	/**
	* @brief 環境光の強さを変更する 呼ばれていない場合環境光は使われない
	* @param aRGB 環境光の強さ 明るい色のほうが強くなる
	*/
	virtual void ChangeAmbientIntensity(DWORD aRGB) const = 0;

	/**
	* @brief 反射光を有効にする
	*/
	virtual void EnableSpecular() const = 0;

	/**
	* @brief 反射光を無効にする
	*/
	virtual void DisaableSpecular() const = 0;

	/**
	* @brief デフォルトのライティングを使用する ウィンドウモードを切り替えた時には再設定する必要がある
	*/
	virtual void DefaultLighting() const = 0;

	/**
	* @brief テクスチャを作成する
	* @param pTexKey テクスチャにつける名前のポインタ キー 連想配列
	* @param pTexPath 画像のパスのポインタ
	*/
	virtual void CreateTex(const TCHAR* pTexKey, const TCHAR* pTexPath) = 0;

	/**
	* @brief 全てのテクスチャの開放
	*/
	virtual void AllTexRelease() = 0;

	/// <summary>
	/// 指定したテクスチャの開放を行う
	/// </summary>
	/// <param name="pTexKey">[in]開放したいテクスチャのパス</param>
	virtual void ReleaseTex(const TCHAR* pTexKey) = 0;

	/**
	* @brief テクスチャを取得する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return テクスチャのポインタ
	*/
	virtual const LPDIRECT3DTEXTURE9 GetTex(const TCHAR* pTexKey) const = 0;

	/**
	* @brief テクスチャが生成されているか判断する
	* @param pTexKey テクスチャを作るときに決めたキーのポインタ
	* @return 存在していたらtrue
	*/
	virtual const bool TexExists(const TCHAR* pTexKey) const = 0;

	/**
	* @brief 現在のカメラの位置を取得する
	* @param[out] pCameraPos カメラ位置を入れる
	*/
	virtual void GetCameraPos(D3DXVECTOR3* pCameraPos) const = 0;

	/**
	* @brief 現在のカメラの位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	virtual void SetCameraPos(float x, float y, float z) = 0;

	virtual void SetCameraPos(const D3DXVECTOR3& rCameraPos) = 0;

	/**
	* @brief 現在のカメラの注視点を取得する
	* @param[out] pEyePoint カメラの注視点を入れる
	*/
	virtual void GetCameraEyePt(D3DXVECTOR3* pEyePoint) const = 0;

	/**
	* @brief 現在のカメラの注視点位置を変更する
	* @param x x座標
	* @param y y座標
	* @param z z座標
	*/
	virtual void SetCameraEyePt(float x, float y, float z) = 0;

	virtual void SetCameraEyePt(const D3DXVECTOR3& rEyePt) = 0;

	/**
	* @brief カメラのビュー行列を取得する
	* @param[out] pView ビュー行列を入れる
	*/
	virtual void GetView(D3DXMATRIX* pView) const = 0;

	/**
	* @brief カメラのプロジェクション行列を取得する
	* @param[out] pProjrction プロジェクション行列を入れる
	*/
	virtual void GetProjection(D3DXMATRIX* pProjrction) const = 0;

	/**
	* @brief カメラを適用させる
	*/
	virtual void SetCameraTransform() = 0;

	/**
	* @brief 引数の行列をビルボード化する、
	* 回転行列なのでかけ合わせる順番は回転行列をかけ合わせるとき
	* @param[in,out] pWorld ビルボード化する行列のポインタ
	*/
	virtual void TransBillBoard(D3DXMATRIX* pWorld) const = 0;

	/// <summary>
	/// 引数のワールド座標をスクリーン座標に直した値を返す
	/// </summary>
	/// <param name="screenPos">[in]ワールド座標に直したいスクリーン座標</param>
	/// <returns>引数をワールド座標に直した値</returns>
	virtual D3DXVECTOR3 TransScreen(const D3DXVECTOR3& Pos) = 0;

	/// <summary>
	/// 引数のスクリーン座標をワールド座標に直した値を返す
	/// </summary>
	/// <param name="worldPos">[in]スクリーン座標に直したいワールド座標</param>
	/// <returns>引数をスクリーン座標に直した値</returns>
	virtual D3DXVECTOR3 TransWorld(const D3DXVECTOR3& Pos) = 0;

	/**
	* @brief XYZ順に回転を行う
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param deg 回転をさせる度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	* @detail 回転行列を作成し、矩形の中心を求め回転の中心を原点に移動させ、回転行列を用いて回転を行い原点へ移動させた分元に戻す
	*/
	virtual void RotateRectXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3& deg, const D3DXVECTOR3& relativeRotateCenter) const = 0;

	/**
	* @brief x軸で回転させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param 度数法での角度
	* @param relativeRotateCenter どれほど回転の中心が矩形の中心よりずれているか
	*/
	virtual void RotateRectX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const = 0;

	virtual void RotateRectY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const = 0;

	virtual void RotateRectZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const = 0;

	/**
	* @brief 矩形を拡縮させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param scaleRate 拡縮率
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	virtual void RescaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR2& scaleRate) const = 0;

	/**
	* @brief 矩形を移動させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param movement 移動量
	*/
	virtual void MoveRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& movement) const = 0;

	/**
	* @brief 矩形を引数の位置に再配置させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param pos 矩形を移動させる座標
	*/
	virtual void LocaleRect(CustomVertex* pCustomVertices, const D3DXVECTOR3& pos) const = 0;

	/**
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param startTU x方向のテクスチャ座標の始まりの値
	* @param startTV y方向のテクスチャ座標の始まりの値
	* @param endTU x方向のテクスチャ座標の終わりの値
	* @param endTV y方向のテクスチャ座標の終わりの値
	*/
	virtual void SetRectTexUV(CustomVertex* pCustomVertices,
		float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const = 0;

	/**
	* @brief 矩形の色を引数の色に変更する
	* @param[in,out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param aRGB アルファ値入りのカラーコード ARGB
	*/
	virtual void SetRectARGB(CustomVertex *pCustomVertices, DWORD aRGB) const = 0;

	/// <summary>
	/// 矩形を上から下にグラデーションさせる
	/// </summary>
	/// <param name="pCustomVertices">[out]グラデーションさせたい頂点情報構造体配列の先頭アドレス</param>
	/// <param name="topARGB">上の色</param>
	/// <param name="bottomARGB">下の色</param>
	virtual void SetTopBottomARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const = 0;

	virtual void SetLeftRightARGB(CustomVertex *pCustomVertices, DWORD leftARGB, DWORD rightARGB) const = 0;

	virtual void SetObliqueToBottomRightARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const = 0;

	virtual void SetObliqueToBottomLeftARGB(CustomVertex *pCustomVertices, DWORD topARGB, DWORD bottomARGB) const = 0;

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
	virtual void FlashRect(CustomVertex* pVertices, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const = 0;

	virtual void FlashRect(VerticesParam* pVerticesParam, int* pFrameCnt, int flashFlameMax, BYTE alphaMax, BYTE alphaMin = 0) const = 0;

	/// <summary>
	/// アルファ値のみを変更する
	/// </summary>
	/// <param name="pVerticesParam">矩形の頂点情報のデータ</param>
	/// <param name="alpha">変更したいアルファ値</param>
	virtual void SetRectAlpha(VerticesParam* pVerticesParam, BYTE alpha) const = 0;

	virtual void SetRectAlpha(CustomVertex* pVertices, BYTE alpha) const = 0;

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
	virtual void CreateRect(CustomVertex *pCustomVertices, const D3DXVECTOR3& center, const D3DXVECTOR3& halfScale,
		DWORD aRGB = 0xFFFFFFFF, float startTU = 0.0f, float startTV = 0.0f, float endTU = 1.0f, float endTV = 1.0f) const = 0;

	/**
	* @brief 頂点データ構造体を引数の値から作成する 回転も行う
	* @param[out] pCustomVertices 頂点データ配列の先頭アドレス
	* @param verticesParam オブジェクトの状態構造体
	*/
	virtual void CreateRect(CustomVertex *pCustomVertices, const VerticesParam& verticesParam) const = 0;

	/**
	* @brief FBXの描画を行う
	* @param rFBXModel FBXのクラス モデルを読み込んだ後でないといけない
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture モデルに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	virtual void Render(const FbxRelated& rFBXModel, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const = 0;

	/**
	* @brief CustomVertexの描画を行う
	* @param pCustomVertices 描画する矩形の頂点データの先頭ポインタ
	* @param pTexture ポリゴンに張り付けるテクスチャのポインタ
	*/
	virtual void Render(const CustomVertex* pCustomVertices, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const = 0;

	/**
	* @brief 3Dの板ポリにテクスチャを張り付けて描画する
	* @param pVertex 板ポリの先頭アドレス
	* @param rMatWorld 拡大回転移動行列をまとめた行列
	* @param pTexture 板ポリに張り付けるテクスチャのポインタ デフォルトで存在している場合はnullptr
	*/
	virtual void Render(const Vertex3D* pVertex3D, const D3DXMATRIX& rWorld, const LPDIRECT3DTEXTURE9 pTexture = nullptr) = 0;

	/// <summary>
	/// 文字の描画を行う
	/// </summary>
	/// <param name="topLeft">[in]左上の座標</param>
	/// <param name="pText">[in]描画したい文字列</param>
	/// <param name="format">文字のフォーマット DT_LEFT(左寄せ)等</param>
	/// <param name="pFont">描画する際に使うフォントオブジェクト</param>
	/// <param name="color">文字の色ARGB</param>
	virtual void Render(const D3DXVECTOR2& topLeft, const TCHAR* pText, UINT format, LPD3DXFONT pFont, DWORD color) = 0;

	/// <summary>
	/// 矩形の描画を行う
	/// </summary>
	/// <param name="verticesParam">頂点情報配列を作成するためのデータ</param>
	/// <param name="pTexture">矩形に張り付けるテクスチャのポインタ</param>
	virtual void Render(const VerticesParam& verticesParam, const LPDIRECT3DTEXTURE9 pTexture = nullptr) const = 0;

	/// <summary>
	/// FBXオブジェクトの作成を行う
	/// </summary>
	/// <param name="pKey">[in]作成するオブジェクトにつけるキー</param>
	/// <param name="pFilePath">[in]作成するオブジェクトのパス</param>
	virtual void CreateFbx(const TCHAR* pKey, const CHAR* pFilePath) = 0;

	/// <summary>
	/// FBXオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">[in]取得したいオブジェクトのキー</param>
	/// <returns>FBXオブジェクトクラスの参照</returns>
	virtual FbxRelated& GetFbx(const TCHAR* pKey) = 0;

	/// <summary>
	/// フォントの全開放
	/// </summary>
	virtual void AllFontRelease() = 0;
	/// <summary>
	/// 指定したフォントの開放
	/// </summary>
	/// <param name="pFontKey">開放したいフォントのキー</param>
	virtual void ReleaseFont(const TCHAR* pFontKey) = 0;

	/// <summary>
	///	フォントオブジェクトの作成
	/// </summary>
	/// <param name="pKey">作成するオブジェクトにつけるキー</param>
	/// <param name="scale">文字の幅</param>
	/// <param name="pFontName">フォントの名前 MSゴシック等</param>
	/// <param name="thickness">文字の太さ</param>
	virtual void CreateFont(const TCHAR* pKey, D3DXVECTOR2 scale, const TCHAR* pFontName, UINT thickness = 0) = 0;

	/// <summary>
	/// 文字が存在しているかを判別する
	/// </summary>
	/// <param name="pKey">判別したいフォントのキー</param>
	/// <returns>存在していればtrue</returns>
	virtual bool FontExists(const TCHAR* pKey) = 0;

	/// <summary>
	/// フォントオブジェクトのゲッタ
	/// </summary>
	/// <param name="pKey">取得したいフォントのキー</param>
	/// <returns>フォントオブジェクトの参照</returns>
	virtual const LPD3DXFONT GetFont(const TCHAR* pKey) = 0;
};

#endif // !I_GAME_LIB_RENDERER_H
