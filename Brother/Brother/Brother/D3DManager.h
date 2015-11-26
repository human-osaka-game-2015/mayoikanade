#ifndef D3DMANAGER_H
#define D3DMANAGER_H

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
	static LPDIRECT3DDEVICE9		pD3Device;
	D3DManager(HWND hwnd,bool isFullWindow=false);
	~D3DManager();
	void Render_Init();
	void Draw_Ready();
	void Draw_End();
	bool isDevice_Lost();
		
};


#endif