/**
* @file Library.cpp
* @brief Libraryクラス
* @author 森本
* @date 12月9日
*/
#include "D3DManager.h"
#include "Library.h"



/**
 * Libraryクラスのコンストラクタ
 * @param[in] hWnd ウィンドウハンドル
 * @param[in] isFullWindow フルウィンドウにするかのフラグ
 * @param[in] isStencil ステンシルを使うかのフラグ
 */
Library::Library(HWND hWnd, bool isFullWindow,bool isStencil) :
m_pD3DManager(NULL), 
m_pDSoundManager(NULL), 
m_pXInput(NULL), 
m_pTexture(NULL), 
m_pVertex(NULL), 
m_pUVSetter(NULL)
{
	//ライブラリクラスの生成
	m_pD3DManager		= new D3DManager(hWnd, isFullWindow,isStencil);
	m_pDSoundManager	= new DSoundManager(hWnd);
	m_pXInput			= new XInput();
	m_pTexture			= new Texture(D3DManager::pD3Device);
	m_pVertex			= new Vertex();
	m_pUVSetter			= new UVSetter();
	m_pStencilManager	= new StencilManager(D3DManager::pD3Device);
	m_pInputDevice		= new InputDevice(hWnd);
}


Library::~Library()
{
	//ライブラリクラスの破棄
	delete m_pInputDevice;
	delete m_pStencilManager;
	delete m_pUVSetter;
	delete m_pVertex;
	delete m_pTexture;
	delete m_pXInput;
	delete m_pDSoundManager;
	delete m_pD3DManager;
}


/**
 * デバイスを取得する関数
 * @return LPDIRECT3DDECVICE9が返る
 */
LPDIRECT3DDEVICE9 Library::GetDevice()
{
	return m_pD3DManager->pD3Device;
}


//--------------------------------------------------------------------------------------
//
//		D3DManager
//
//--------------------------------------------------------------------------------------

/**
 * 描画時のSetRenderState関数をまとめて読んでくれる
 */
void Library::RenderInit()
{
	m_pD3DManager->RenderInit();
}

/**
 * 描画前の処理を行ってくれる
 */
void Library::DrawReady()
{
	m_pD3DManager->DrawReady();
}

/**
 * 描画後の処理を行ってくれる
 */
void Library::DrawEnd()
{
	m_pD3DManager->DrawEnd();
}



//--------------------------------------------------------------------------------------
//
//		DSoundManager
//
//--------------------------------------------------------------------------------------

/**
 * サウンドのロード関数(wavのみ)
 * @param[in] filename 読み込むファイルの名前
 * @param[in] key 格納先のキー
 * @return 成功したかの情報が返ってくる
 */
int Library::SoundLoad(char* filename, int Key)
{
	return m_pDSoundManager->SoundLoad(filename, Key);
}

/**
 * サウンドの解放関数
 * @param[in] Key 解放する音声の格納先のキー
 */
void Library::ReleaseSound(int Key)
{
	m_pDSoundManager->ReleaseSound(Key);
}

/**
 * サウンドの解放関数
 * @param[in] Key 操作する音声の格納先のキー
 * @param[in] operation 音声に対する操作
 */
void Library::SoundOperation(int Key, SOUND_OPERATION operation)
{
	m_pDSoundManager->SoundOperation(Key, operation);
}


//--------------------------------------------------------------------------------------
//
//		Texture
//
//--------------------------------------------------------------------------------------

/**
 * テクスチャの読み込み
 * @param[in] name 読み込むファイルの名前
 * @param[in] key 格納先のキー
 * @param[in] alpha 透過する色の指定(α)
 * @param[in] red 透過する色の指定(赤)
 * @param[in] green 透過する色の指定(緑)
 * @param[in] blue 透過する色の指定(青)
 * @return 成功したかどうかの情報
 */
int Library::LoadTextureEx(const char* name, int key, int alpha = 255, int red = 0, int green = 255, int blue = 0)
{
	return m_pTexture->LoadTextureEx(name, key, alpha, red, green, blue);
}

/**
 * テクスチャの解放
 * @param[in] key 解放する画像の格納先のキー
 */
void Library::ReleaseTexture(int key)
{
	m_pTexture->ReleaseTexture(key);
}

/** 
 * 描画関数
 * @param[in] key 描画するテクスチャの格納先キー
 * @param[in] pVertex 描画する頂点座標
 */
void Library::DrawTexture(int key, CustomVertex* pVertex)
{
	m_pTexture->DrawTexture(key, pVertex);
}



//--------------------------------------------------------------------------------------
//
//		Vertex
//
//--------------------------------------------------------------------------------------

/**
 * Position構造体からxy情報を取得してpVertexに出力する
 * @param[in] pos xy情報を取得するposition構造体
 * @param[out] pVertex xy情報を出力するCustomVertex
 */
void Library::xySet(Position pos, CustomVertex* pVertex)
{
	m_pVertex->xySet(pos, pVertex);
}

/**
 * 頂点座標の回転関数
 * @param[out] pVertex 回転する頂点
 * @param[in] pos その頂点の位置
 * @param[in] angle 回転する角度
 */
void Library::Turn(CustomVertex* pVertex, Position* pos, double angle)
{
	m_pVertex->Turn(pVertex, pos, angle);
}


//--------------------------------------------------------------------------------------
//
//		UVSetter
//
//--------------------------------------------------------------------------------------

/**
 * ファイル情報の入ったcsvを読み込む関数
 * @param[in] name 読み込むファイルの名前
 * @param[in] fileNum 読み込む情報量
 * @return 成功したかどうか(成功したら0が返る)
 */
int Library::FileInfoSet(const char* name, int fileNum)
{
	return m_pUVSetter->FileInfoSet(name, fileNum);
}


/**
 * 頂点情報の入ったcsvを読み込む関数
 * @param[in] name 読み込むファイルの名前
 * @param[in] vertexNum 読み込む情報量
 * @return 成功したかどうか(成功したら0が返る)
 */
int Library::VertexInfoSet(const char* name, int vertexNum)
{
	return m_pUVSetter->VertexInfoSet(name, vertexNum);
}

/**
 * アニメーション情報の入ったcsvを読み込む関数
 * @param[in] name 読み込むファイルの名前
 * @param[in] animaNum 読み込む情報量
 * @return 成功したかどうか(成功したら0が返る)
 */
int Library::AnimaInfoSet(const char* name, int animaNum)
{
	return m_pUVSetter->AnimaInfoSet(name, animaNum);
}

/**
 * ファイルの情報の解放
 */
void Library::FileInfoRelease()
{
	m_pUVSetter->FileInfoRelease();
}

/**
 * 頂点情報の解放
 */
void Library::VertexInfoRelease()
{
	m_pUVSetter->VertexInfoRelease();
}

/**
 * アニメーション情報の解放
 */
void Library::AnimaInfoRelease()
{
	m_pUVSetter->AnimaInfoRelease();
}

/**
 * 頂点情報をPosition構造体に出力する
 * @param[in] vertexNum 参照する頂点情報の番号 
 * @param[out] pPos 頂点情報が出力されるPosition構造体
 */
void Library::MakePosition(int vertexNum, Position* pPos)
{
	m_pUVSetter->MakePosition(vertexNum, pPos);
}

/**
 * 頂点情報をCustomVertex構造体に出力する
 * @param[in] vertexNum 参照する頂点情報の番号
 * @param[out] pVertex 頂点情報が出力されるCustomVertex構造体
 */
void Library::MakeVertex(int vertexNum, CustomVertex* pVertex)
{
	m_pUVSetter->MakeVertex(vertexNum, pVertex);
}

/**
 * アニメーション情報の初期化
 * @param[in] animaNum 初期化するアニメーション
 */
void Library::InitAnima(int animaNum)
{
	m_pUVSetter->InitAnima(animaNum);
}

/**
 * 次の画像を教えてくれる関数
 * @param[in] animaNum アニメーション番号
 * @return 次に表示する画像の番号
 */
int Library::AnimaControl(int animaNum)
{
	return m_pUVSetter->AnimaControl(animaNum);
}


/**
 * 反転させる関数
 * @param[out] pVertex 反転するCustomVertex
 * @param[in] rev 横反転か縦反転か
 */
void Library::UVReversal(CustomVertex* pVertex, REVERSAL_NUM rev)
{
	m_pUVSetter->UVReversal(pVertex, rev);
}


//--------------------------------------------------------------------------------------
//
//		XInput
//
//--------------------------------------------------------------------------------------

/**
 * コントローラーの状態チェック
 * @param[in] pad チェックするGAMEPAD
 */
void Library::Check(XINPUTPAD pad)
{
	m_pXInput->Check(pad);
}

/**
 * ボタンの状態を取得する関数
 * @param[in] id 取得するボタン
 * @param[in] pad チェックするGamePad
 * @return チェックしたボタンの状態
 */
PADSTATE Library::GetButtonState(XINPUT_ID id, XINPUTPAD pad)
{
	return m_pXInput->GetButtonState(id, pad);
}


/**
 * スティックの状態を取得する関数
 * @param[in] id 取得するスティック
 * @param[in] pad チェックするGamePad
 * @return チェックしたスティックの状態
 */
bool Library::GetAnalogState(ANALOGPAD id, XINPUTPAD pad)
{
	return m_pXInput->GetAnalogState(id, pad);
}



//--------------------------------------------------------------------------------------
//
//		StencilManager
//
//--------------------------------------------------------------------------------------

/**
 * ステンシルの描画前処理
 */
void Library::StencilDrawReady()
{
	m_pStencilManager->StencilDrawReady();
}

/**
 * ステンシルの描画後処理
 */
void Library::StencilDrawEnd()
{
	m_pStencilManager->StencilDrawEnd();
}


/**
 * ステンシルの参照値のセット
 * @param[in] ref 設定する参照値
 */
void Library::StencilRefSet(BYTE ref)
{
	m_pStencilManager->StencilRefSet(ref);
}

/**
 * ステンシル描画
 * @param[in] vertex 描画する頂点情報
 */
void Library::StencilDraw(CustomVertex* vertex)
{
	m_pStencilManager->StencilDraw(vertex);
}


/**
 * αテストの準備
 * @param[in] ref αテストを行う際の基準値
 */
void Library::AlphaTestReady(BYTE ref)
{
	m_pStencilManager->AlphaTestReady(ref);
}

/**
 * αテストを切る
 */
void Library::AlphaTestEnd()
{
	m_pStencilManager->AlphaTestEnd();
}


/**
 * ステンシルテストの終了処理
 */
void Library::StencilTestEnd()
{
	m_pStencilManager->StencilTestEnd();
}



//--------------------------------------------------------------------------------------
//
//		InputDevice
//
//--------------------------------------------------------------------------------------

/**
 * DirectInputのキーの初期化
 * @return 成功したかしてないか(成功したらS_OK)
 */
HRESULT Library::InitDinputKey()
{
	return m_pInputDevice->InitDinputKey();
}

/**
 * DirectInputのマウスの初期化
 * @return 成功したかしてないか(成功したらS_OK)
 */
HRESULT Library::InitDinputMouse()
{
	return m_pInputDevice->InitDinputMouse();
}


/**
 * キーの状態チェック関数
 * @param[out] Key キーの状態を格納する配列
 * @param[in] DIK チェックするキー
 */
void Library::KeyCheck(KEYSTATE* Key, int DIK)
{
	m_pInputDevice->KeyCheck(Key, DIK);
}


/**
 * マウスの状態チェック関数
 * @param[out] Mouse マウスの状態を出力するMOUSEKIND構造体
 */
void Library::MouseCheck(MOUSEKIND* Mouse)
{
	m_pInputDevice->MouseCheck(Mouse);
}

