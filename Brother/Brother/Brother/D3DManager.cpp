/**
 * @file D3DManager.cpp
 * @brief D3DManagerクラス
 * @author 森本
 * @date 11月9日
 */

#include "D3DManager.h"

LPDIRECT3DDEVICE9 D3DManager::pD3Device;



D3DManager::D3DManager(HWND hwnd) :m_pDirect3D(NULL)
{

	//DirectX オブジェクトの生成
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//Display Mode の設定
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_d3ddm);
	
	ZeroMemory(&m_d3dpp,sizeof(D3DPRESENT_PARAMETERS));

	m_d3dpp.BackBufferFormat = m_d3ddm.Format;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.Windowed = TRUE;

	//デバイスを作る
	m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_d3dpp, &pD3Device);
}

D3DManager::~D3DManager()
{
	pD3Device->Release();
	m_pDirect3D->Release();
	pD3Device = NULL;
	m_pDirect3D = NULL;
}


//描画方法の設定
void D3DManager::Render_Init()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

//描画の開始
void D3DManager::Draw_Ready()
{
	//画面の消去
	pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//描画の開始
	pD3Device->BeginScene();


}

//描画の終了
void D3DManager::Draw_End()
{
	//描画の終了
	pD3Device->EndScene();

	//表示
	pD3Device->Present(NULL, NULL, NULL, NULL);
}

//Deviceが失われているのかをチェックする
bool D3DManager::isDevice_Lost()
{
	if (D3DManager::pD3Device == NULL)
	{
		return true;
	}
	return false;
}
