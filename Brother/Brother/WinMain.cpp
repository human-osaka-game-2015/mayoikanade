#include <windows.h>
#include <crtdbg.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "GameMain.h"
#include "SceneManager.h"

#define WINDOWTITLE "迷い兄弟"
#define CDCLSEXTRA 0
#define CDWNDEXTRA 0
#define ONE_MILLISECOND 1
#define DEFAULT_WMSGFILTERMIN 0
#define DEFAULT_WMSGFILTERMAX 0
#define DEFAULT_POSTMESSAGE_WPARAM 0
#define DEFAULT_POSTMESSAGE_LPARAM 0
#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 1024
#define DEFAULTFRAME 1000 / 60

#define EXITCODE 0
#define NORMAL_RETURN 0

//#define FULLWINDOW
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


//-------------------------------------------------------------
//
//	メインルーチン
//
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASS winc;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = CDCLSEXTRA;
	winc.cbWndExtra = CDWNDEXTRA;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WINDOWTITLE;
	
	RegisterClass(&winc);

#ifdef FULLWINDOW
	hWnd = CreateWindow(
		WINDOWTITLE,
		WINDOWTITLE,
		WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOWWIDTH,
		WINDOWHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	DEVMODE devMode;

	devMode.dmSize       = sizeof(DEVMODE);
	devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
	devMode.dmPelsWidth  = WINDOWWIDTH;
	devMode.dmPelsHeight = WINDOWHEIGHT;
	ShowWindow(hWnd, SW_SHOWNORMAL);
	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

#else
	hWnd = CreateWindow(
		WINDOWTITLE,
		WINDOWTITLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOWWIDTH,
		WINDOWHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
#endif



	GameMain Main(hWnd);
	
	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(ONE_MILLISECOND);

	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(ONE_MILLISECOND);
		if (PeekMessage(&msg, NULL, DEFAULT_WMSGFILTERMIN, DEFAULT_WMSGFILTERMAX, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= DEFAULTFRAME)
			{
				if (Main.m_pSceneManager->Control())
				{
					break;
				}
				Main.m_pSceneManager->Draw();

				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(ONE_MILLISECOND);


	return static_cast<int>(msg.wParam);
}



//-------------------------------------------------------------
//
//	メッセージ処理
//
//-------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(EXITCODE);
		return NORMAL_RETURN;
	case WM_KEYDOWN:
		if (wp == VK_ESCAPE) 
		{
			PostMessage(hWnd, WM_CLOSE, DEFAULT_POSTMESSAGE_WPARAM, DEFAULT_POSTMESSAGE_LPARAM);
			return NORMAL_RETURN;
		}
		break;
#ifdef FULLWINDOW
	case WM_SETCURSOR:
		SetCursor(NULL);
		return NORMAL_RETURN;
#endif

	}

	return DefWindowProc(hWnd, msg, wp, lp);

}