/**
 * @file D3DManager.cpp
 * @brief D3DManager�N���X
 * @author �X�{
 * @date 11��9��
 */

#include "D3DManager.h"

LPDIRECT3DDEVICE9 D3DManager::pD3Device;



D3DManager::D3DManager(HWND hwnd) :m_pDirect3D(NULL)
{

	//DirectX �I�u�W�F�N�g�̐���
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//Display Mode �̐ݒ�
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_d3ddm);
	
	ZeroMemory(&m_d3dpp,sizeof(D3DPRESENT_PARAMETERS));

	m_d3dpp.BackBufferFormat = m_d3ddm.Format;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.Windowed = TRUE;

	//�f�o�C�X�����
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


//�`����@�̐ݒ�
void D3DManager::Render_Init()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

//�`��̊J�n
void D3DManager::Draw_Ready()
{
	//��ʂ̏���
	pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//�`��̊J�n
	pD3Device->BeginScene();


}

//�`��̏I��
void D3DManager::Draw_End()
{
	//�`��̏I��
	pD3Device->EndScene();

	//�\��
	pD3Device->Present(NULL, NULL, NULL, NULL);
}

//Device�������Ă���̂����`�F�b�N����
bool D3DManager::isDevice_Lost()
{
	if (D3DManager::pD3Device == NULL)
	{
		return true;
	}
	return false;
}
