#include "StencilManager.h"


/**
 * StencilManagerクラスのコンストラクタ
 */
StencilManager::StencilManager(LPDIRECT3DDEVICE9 pDevice) :
m_pDevice(pDevice),
m_StencilRef(0x05)
{

}

/**
 * StencilManagerクラスのデストラクタ
 */
StencilManager::~StencilManager()
{

}


/**
 * ステンシルの描画前処理
 */
void StencilManager::StencilDrawReady()
{
	//ステンシルバッファ上のデータ消去
	m_pDevice->Clear(0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);


	//ステンシルテストの設定***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);		//有効

	//深度テストの設定******************************************
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);		//必ず不合格

	//ステンシル参照値の設定************************************
	m_pDevice->SetRenderState(D3DRS_STENCILREF, m_StencilRef);			

	//ステンシルマスクの設定************************************
	m_pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffffにする
	m_pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffffにする

	//ステンシルバッファに書き込む条件（比較関数）の設定********
	m_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	//絶対に書き込む。

	//書き込む値の設定******************************************
	//ステンシルテストに失敗した場合はなにもしない
	m_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//何もしない
	//ステンシルテストに成功して、zバッファテストにに失敗した場合
	m_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//ステンシル参照値を書き込む。
	//ステンシル、z、両方成功した場合
	m_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//何もしない

}

/**
 * ステンシルの描画後処理
 */
void StencilManager::StencilDrawEnd()
{

	//深度テストの設定*****************************************
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//ステンシル参照値の設定***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILREF, m_StencilRef);

	//ステンシルマスクの設定***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffffにする
	m_pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffffにする


	m_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);


	//書き込む値の設定***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//何もしない
	m_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	//何もしない
	m_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//何もしない

}

/**
 * ステンシルテストの終了処理
 */
void StencilManager::StencilTestEnd()
{
	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
}

/**
 * ステンシルの参照値のセット
 * @param[in] ref 設定する参照値
 */
void StencilManager::StencilRefSet(BYTE ref)
{
	m_StencilRef = ref;
}

/**
 * ステンシル描画
 * @param[in] vertex 描画する頂点情報
 */
void StencilManager::StencilDraw(CustomVertex* pvertex)
{

	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pvertex,
		sizeof(CustomVertex));
}

/**
 * αテストの準備
 * @param[in] ref αテストを行う際の基準値
 */
void StencilManager::AlphaTestReady(BYTE ref)
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, ref);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_EQUAL);
}

/**
 * αテストを切る
 */
void StencilManager::AlphaTestEnd()
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

