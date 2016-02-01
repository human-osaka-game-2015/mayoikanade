#ifndef D3DMANAGER_H
#define D3DMANAGER_H


#define DEFAULT_WINDOW_HEIGHT 1024			//�f�t�H���g��BackCufferHeight
#define DEFAULT_WINDOW_WIDTH 1280			//�f�t�H���g��BackCufferWidth
#define DEFAULT_BACKBUFFERCOUNT 1			//�f�t�H���g��BackBufferCound
#define DEFAULT_CLEARCOLOR 0x00				//�f�t�H���g��CLEARCOLOR
#define DEFAULT_TEXTURE_STAGE 0				//�f�t�H���g��Texture�X�e�[�W
#define DEFAULT_CLEAR_COUNT 0				//�f�t�H���g��ClearCount
#define DEFAULT_CLEAR_Z 1.0					//�f�t�H���g�̃N���AZ�o�b�t�@
#define DEFAULT_CLEAR_STENCIL 0				//�f�t�H���g�̃N���A�X�e���V���o�b�t�@

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