/**
 * @file D3DManager.cpp
 * @brief D3DManager�N���X
 * @author �X�{
 * @date 11��9��
 */

#include "D3DManager.h"

LPDIRECT3DDEVICE9 D3DManager::pD3Device;


/**
 * D3DManager�N���X�̃R���X�g���N�^
 * @param[in] hWnd �E�B���h�E�n���h��
 * @param[in] isFullWindow �t���X�N���[���ɂ��邩�̎w��
 * @param[in] isStencilBuffer �X�e���V���o�b�t�@���g�����̎w��
 */
D3DManager::D3DManager(HWND hwnd, bool isFullWindow, bool isStencilBuffer) :
m_pDirect3D(NULL)
{

	//DirectX �I�u�W�F�N�g�̐���
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//Display Mode �̐ݒ�
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
	

	//�f�o�C�X�����
	m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_d3dpp, &pD3Device);
}

/**
 * D3DManager�N���X�̃f�X�g���N�^
 */
D3DManager::~D3DManager()
{
	pD3Device->Release();
	m_pDirect3D->Release();
	pD3Device = NULL;
	m_pDirect3D = NULL;
}


/**
 * �`��O��SetRenderState�֐�
 */
void D3DManager::RenderInit()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
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
 * �`��O����
 */
void D3DManager::DrawReady()
{
	//��ʂ̏���
	pD3Device->Clear(DEFAULT_CLEAR_COUNT, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(DEFAULT_CLEARCOLOR, DEFAULT_CLEARCOLOR, DEFAULT_CLEARCOLOR), DEFAULT_CLEAR_Z, DEFAULT_CLEAR_STENCIL);

	//�`��̊J�n
	pD3Device->BeginScene();
}

/**
 * �`��㏈��
 */
void D3DManager::DrawEnd()
{
	//�`��̏I��
	pD3Device->EndScene();

	//�\��
	pD3Device->Present(NULL, NULL, NULL, NULL);
}


/**
 * �f�o�C�X�������Ă��邩���`�F�b�N����֐�
 */
bool D3DManager::isDeviceLost()
{
	if (D3DManager::pD3Device == NULL)
	{
		return true;
	}
	return false;
}
