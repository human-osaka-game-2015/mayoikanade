#include <windows.h>
#include <crtdbg.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>

#include "GameMain.h"
#include"SceneManager.h"
#define WINDOWTITLE "�����Z��"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

#define FULLWINDOW//�R�����g�A�E�g�폜����ƃt���X�N���J�[�\���폜�ݒ�B


//-------------------------------------------------------------
//
//	���C�����[�`��
//
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASS winc;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WINDOWTITLE;

	if (!RegisterClass(&winc)) return 0;

	int dH = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME) * 2;
	int dW = GetSystemMetrics(SM_CXFRAME) * 2;
#ifdef FULLWINDOW//�t���X�N�ݒ�
	hWnd = CreateWindow(
		WINDOWTITLE,
		WINDOWTITLE,
		WS_VISIBLE | WS_POPUP,//�������̍폜
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280 + dW,
		1024 + dH,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	ShowWindow(hWnd, SW_MAXIMIZE); // �E�B���h�E��\��SW_MAXIMIZE����������ƃt���X�N���ۂ��Ȃ�܂����B

#else
	hWnd = CreateWindow(
		WINDOWTITLE,
		WINDOWTITLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280 + dW,
		1024 + dH,
		NULL,
		NULL,
		hInstance,
		NULL
		);
#endif
	
	//�E�B���h�E�T�C�Y�擾
	//�E�B���h�E�T�C�Y�̓I�u�W�F�N�g�ɓn���悤�ɂ��邱��
	RECT lprc;
	GetWindowRect(hWnd, &lprc);
	lprc.right += dW;
	lprc.bottom += dH;
	//��ʃT�C�Y
	//1374
	//798
	//����
	//687
	//399

	if (!hWnd) return 0;

	GameMain Main(hWnd);
	
	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)
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
	timeEndPeriod(1);


	return (int)msg.wParam;
}



//-------------------------------------------------------------
//
//	���b�Z�[�W����
//
//-------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{
	case WM_DESTROY:	//	�E�C���h�E������ꂽ���Ƃ�
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN://�G�X�P�[�v�L�[�Ńf�o�b�O�I��
		if (wp == VK_ESCAPE) 
		{
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0L;
		}
		break;
#ifdef FULLWINDOW
	case WM_SETCURSOR://�E�B���h�E��ʂł̃J�[�\���폜
		SetCursor(NULL);
		return 0L;
#endif

	}

	return DefWindowProc(hWnd, msg, wp, lp);

}