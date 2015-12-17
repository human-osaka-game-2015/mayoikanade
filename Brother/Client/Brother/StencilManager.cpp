#include "StencilManager.h"
#include "D3DManager.h"



StencilManager::StencilManager() :m_StencilRef(0x05)
{

}

StencilManager::~StencilManager()
{

}



void StencilManager::StencilDrawReady()
{
	//ステンシルバッファ上のデータ消去
	D3DManager::pD3Device->Clear(0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);


	//ステンシルテストの設定***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILENABLE, TRUE);		//有効

	//深度テストの設定******************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);		//必ず不合格

	//ステンシル参照値の設定************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILREF, m_StencilRef);			

	//ステンシルマスクの設定************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffffにする
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffffにする

	//ステンシルバッファに書き込む条件（比較関数）の設定********
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	//絶対に書き込む。

	//書き込む値の設定******************************************
	//ステンシルテストに失敗した場合はなにもしない
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//何もしない
	//ステンシルテストに成功して、zバッファテストにに失敗した場合
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//ステンシル参照値を書き込む。
	//ステンシル、z、両方成功した場合
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//何もしない

}

void StencilManager::StencilDrawEnd()
{

	//深度テストの設定*****************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//ステンシル参照値の設定***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILREF, m_StencilRef);

	//ステンシルマスクの設定***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffffにする
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffffにする


	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);


	//書き込む値の設定***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//何もしない
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	//何もしない
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//何もしない

}

void StencilManager::StencilTestEnd()
{
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILENABLE, false);
}

void StencilManager::StencilRefSet(BYTE ref)
{
	m_StencilRef = ref;
}



void StencilManager::StencilDraw(CustomVertex* pvertex)
{

	D3DManager::pD3Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pvertex,
		sizeof(CustomVertex));
}

void StencilManager::AlphaTestReady(BYTE ref)
{
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHAREF, ref);
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_EQUAL);
}

void StencilManager::AlphaTestEnd()
{
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

