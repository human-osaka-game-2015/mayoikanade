#ifndef D3DMANAGER_H
#define D3DMANAGER_H


#define DEFAULT_WINDOW_HEIGHT 1024			//デフォルトのBackCufferHeight
#define DEFAULT_WINDOW_WIDTH 1280			//デフォルトのBackCufferWidth
#define DEFAULT_BACKBUFFERCOUNT 1			//デフォルトのBackBufferCound
#define DEFAULT_CLEARCOLOR 0x00				//デフォルトのCLEARCOLOR
#define DEFAULT_TEXTURE_STAGE 0				//デフォルトのTextureステージ
#define DEFAULT_CLEAR_COUNT 0				//デフォルトのClearCount
#define DEFAULT_CLEAR_Z 1.0					//デフォルトのクリアZバッファ
#define DEFAULT_CLEAR_STENCIL 0				//デフォルトのクリアステンシルバッファ

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>


class D3DManager
{
private:
	LPDIRECT3D9				m_pDirect3D;
	D3DPRESENT_PARAMETERS	m_d3dpp;
	D3DDISPLAYMODE			m_d3ddm;

public:
	D3DManager(HWND hwnd, bool isFullWindow = false, bool isStencilBuffer = false);
	~D3DManager();
	void RenderInit();
	void DrawReady();
	void DrawEnd();
	bool isDeviceLost();
	
	static LPDIRECT3DDEVICE9	pD3Device;

};


#endif