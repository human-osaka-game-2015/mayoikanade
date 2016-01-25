/**
 * @file D3DManager.cpp
 * @brief D3DManagerクラス
 * @author 森本
 * @date 11月9日
 */

#include "D3DManager.h"

LPDIRECT3DDEVICE9 D3DManager::pD3Device;


/**
 * D3DManagerクラスのコンストラクタ
 * @param[in] hWnd ウィンドウハンドル
 * @param[in] isFullWindow フルスクリーンにするかの指定
 * @param[in] isStencilBuffer ステンシルバッファを使うかの指定
 */
D3DManager::D3DManager(HWND hwnd, bool isFullWindow, bool isStencilBuffer) :
m_pDirect3D(NULL)
{

	//DirectX オブジェクトの生成
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//Display Mode の設定
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_d3ddm);
	
	ZeroMemory(&m_d3dpp,sizeof(D3DPRESENT_PARAMETERS));

	m_d3dpp.BackBufferCount = DEFAULT_BACKBUFFERCOUNT;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	if (isFullWindow)
	{
		m_d3dpp.BackBufferWidth  = DEFAULT_WINDOW_WIDTH;
		m_d3dpp.BackBufferHeight = DEFAULT_WINDOW_HEIGHT;
		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_d3dpp.Windowed = FALSE;
	}
	else
	{
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3dpp.Windowed = TRUE;
	}

	if (isStencilBuffer)
	{
		m_d3dpp.EnableAutoDepthStencil = TRUE;
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	}
	

	//デバイスを作る
	m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_d3dpp, &pD3Device);
}

/**
 * D3DManagerクラスのデストラクタ
 */
D3DManager::~D3DManager()
{
	pD3Device->Release();
	m_pDirect3D->Release();
	pD3Device = NULL;
	m_pDirect3D = NULL;
}


/**
 * 描画前のSetRenderState関数
 */
void D3DManager::RenderInit()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pD3Device->SetTextureStageState(DEFAULT_TEXTURE_STAGE, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(DEFAULT_TEXTURE_STAGE, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pD3Device->SetTextureStageState(DEFAULT_TEXTURE_STAGE, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pD3Device->SetTextureStageState(DEFAULT_TEXTURE_STAGE, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(DEFAULT_TEXTURE_STAGE, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pD3Device->SetTextureStageState(DEFAULT_TEXTURE_STAGE, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

/**
 * 描画前処理
 */
void D3DManager::DrawReady()
{
	//画面の消去
	pD3Device->Clear(DEFAULT_CLEAR_COUNT, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(DEFAULT_CLEARCOLOR, DEFAULT_CLEARCOLOR, DEFAULT_CLEARCOLOR), DEFAULT_CLEAR_Z, DEFAULT_CLEAR_STENCIL);

	//描画の開始
	pD3Device->BeginScene();
}

/**
 * 描画後処理
 */
void D3DManager::DrawEnd()
{
	//描画の終了
	pD3Device->EndScene();

	//表示
	pD3Device->Present(NULL, NULL, NULL, NULL);
}


/**
 * デバイスが失われているかをチェックする関数
 */
bool D3DManager::isDeviceLost()
{
	if (D3DManager::pD3Device == NULL)
	{
		return true;
	}
	return false;
}
