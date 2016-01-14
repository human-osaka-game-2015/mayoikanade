#include "Server.h"

#include "ServerGameScene.h"
#include "Library.h"
#include "ServerModeManager.h"
#include "SceneChangeListener.h"
#include "ServerYoungerBrother.h"
#include "ServerBrother.h"
#include "ServerMap.h"
#include "ServerCollisionChecker.h"
#include "ServerText.h"
#include "ServerShadow.h"
#include "ServerGameTimeManager.h"
#include "ServerDrawPositionSetter.h"


//�T�[�o�[
DWORD WINAPI ServerGameScene::Connect(LPVOID vpGameScene)
{
	ServerGameScene* pGameScene = static_cast<ServerGameScene*>(vpGameScene);
	Server BrotherServer("8000");

	ZeroMemory(pGameScene->m_RecvData.CData, sizeof(pGameScene->m_RecvData.CData));
	ZeroMemory(pGameScene->m_SendData.SData, sizeof(pGameScene->m_SendData.SData));

	BrotherServer.Clientlisten();

	
	//�ʒu�̓�������^�C�~���O���Ƃ�B�ł������A�g��Ȃ��Ȃ�Ǝv���B
	static int SyncCount = 0;

	//�T�[�o�[�ő���M���鎞�̔z��̃f�[�^���e-------------------------------------------------------------
	// 0 LEFT
	// 1 RIGHT
	// 2 DOWN
	// 3 UP
	// 4 A
	// 5 B
	//-------------------------------------------------------------------------------------------------

	*pGameScene->m_pisConnect = true;
	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	while (pGameScene->m_isGameScene)
	{
		SyncNow = timeGetTime();

		Sleep(1);
		if (pGameScene->m_pisConnect != NULL && SyncNow - SyncOld >= 1000 / 60)
		{
			bool isConnect = *pGameScene->m_pisConnect;
			if (isConnect == true)
			{
				char* recvptr = reinterpret_cast<char*>(&pGameScene->m_RecvData);
				BrotherServer.recvData(recvptr, sizeof(pGameScene->m_RecvData));
				//�ʒu�𓯊������邽�߂����Ǎ��́A���܂��s���ĂȂ��̂�
				//if (SyncCount % 120 == 0)
				//{
				//	pGameScene->SetYoungBrotherPos(&pGameScene->m_RecvData.Yposx, &pGameScene->m_RecvData.Yposy);
				//}
				for (int i = 0; i < 4; i++)
				{
					if (pGameScene->m_RecvData.CData[i] == 1)
					{
						pGameScene->m_ClientPadState[i] = true;
					}
					else
					{
						pGameScene->m_ClientPadState[i] = false;
					}
				}


				//�N���C�A���g�̃X�e�B�b�N�̃f�[�^���ڂ�
				pGameScene->m_ClientPadOldState[ANALOG_LEFT] = pGameScene->m_ClientPadState[ANALOG_LEFT];
				pGameScene->m_ClientPadOldState[ANALOG_RIGHT] = pGameScene->m_ClientPadState[ANALOG_RIGHT];
				pGameScene->m_ClientPadOldState[ANALOG_DOWN] = pGameScene->m_ClientPadState[ANALOG_DOWN];
				pGameScene->m_ClientPadOldState[ANALOG_UP] = pGameScene->m_ClientPadState[ANALOG_UP];

				//���C�u�����̏C���ɂ��Ȃ�̂ł��܂͂����
				for (int i = 4; i < 6; i++)
				{
					if (pGameScene->m_RecvData.CData[i] == 1)
					{
						if (pGameScene->m_ClientButtonState[i - 4] == PAD_PUSH || pGameScene->m_ClientButtonState[i - 4] == PAD_ON)
						{
							pGameScene->m_ClientButtonState[i - 4] = PAD_ON;
						}
						else
						{
							pGameScene->m_ClientButtonState[i - 4] = PAD_PUSH;
						}
					}
					else if (pGameScene->m_RecvData.CData[i] == 0)
					{
						if (pGameScene->m_ClientButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ClientButtonState[i - 4] == PAD_OFF)
						{
							pGameScene->m_ClientButtonState[i - 4] = PAD_OFF;
						}
						else
						{
							pGameScene->m_ClientButtonState[i - 4] = PAD_RELEASE;
						}
					}
				}


				//�T�[�o�[���f�[�^���l�߂�
				for (int i = 0; i < 4; i++)
				{
					if (pGameScene->m_PadState[i] == true)
					{
						pGameScene->m_SendData.SData[i] = 1;
					}
					else
					{
						pGameScene->m_SendData.SData[i] = 0;
					}
				}

				for (int i = 4; i < 6; i++)
				{
					if (pGameScene->m_ButtonState[i - 4] == PAD_PUSH || pGameScene->m_ButtonState[i - 4] == PAD_ON)
					{
						pGameScene->m_SendData.SData[i] = 1;
					}
					else if (pGameScene->m_ButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ButtonState[i - 4] == PAD_OFF)
					{
						pGameScene->m_SendData.SData[i] = 0;
					}
				}
				//�ʒu�𓯊������邽�߂����Ǎ��́A���܂��s���ĂȂ��̂�
				//pGameScene->GetBrotherPos(&pGameScene->m_SendData.Bposx, &pGameScene->m_SendData.Bposy);
				char* sendptr = reinterpret_cast<char*>(&pGameScene->m_SendData);
				BrotherServer.sendData(sendptr, sizeof(pGameScene->m_SendData.SData));

				ZeroMemory(&pGameScene->m_RecvData, sizeof(pGameScene->m_RecvData));
				ZeroMemory(&pGameScene->m_SendData, sizeof(pGameScene->m_SendData));

				SyncCount++;
				//*pGameScene->m_pisConnect = false;
			}

		}
	}
	timeEndPeriod(1);

	ExitThread(TRUE);
}

DWORD WINAPI ServerGameScene::Synchro(LPVOID vpGameScene)
{
	ServerGameScene* pGameScene = static_cast<ServerGameScene*>(vpGameScene);
	while (pGameScene->m_isGameScene)
	{
	}
	ExitThread(TRUE);
}


ServerGameScene::ServerGameScene(Library* pLibrary, HWND hWnd, bool* pisGameClear) :
Scene(pLibrary),
m_hWnd(hWnd),
m_pisGameClear(pisGameClear),
m_isGameScene(true),
m_pisConnect(&m_isConnect)
{

	for (int i = 0; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}
	//GameScene�̉摜��csv�̓ǂݍ���
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("GameTex.csv", GAME_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfoSet("Gameanimation.csv", GAMEANIMA_MAX);
	m_pLibrary->LoadTextureEx("GameScene.png", TEX_GAME, 255, 0, 255, 0);
	m_pLibrary->LoadTextureEx("ConnectingWait.png", CONNECTING_WAIT, 255, 0, 255, 255);
	m_pLibrary->LoadTextureEx("en.png", STENCIL, 255, 0, 255, 255);

	m_pLibrary->SoundLoad("S_G_BGM.wav", GAME_BGM);
	m_pLibrary->SoundLoad("se_maoudamashii_se_switch01.wav", GAME_SWITCH01);

	//�������[�v
	m_pLibrary->SoundOperation(GAME_BGM, SOUND_LOOP);

	m_pSceneChangeListener = new SceneChangeListener(&m_NextScene,m_pisGameClear);
	m_pMap					= new ServerMap(m_pLibrary);
	m_pCollisionChecker		= new ServerCollisionChecker(m_pMap);
	m_pDrawPositionSetter = new ServerDrawPositionSetter(m_pMap);
	m_pGameTimeManager		= new ServerGameTimeManager(&m_time);
	m_pBrother				= new ServerBrother(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager);
	m_pYoungerBrother		= new ServerYoungerBrother(m_pLibrary, m_ClientPadState, m_ClientPadOldState, m_ClientButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager, m_pBrother);
	m_pShadow = new ServerShadow(m_pLibrary, m_pGameTimeManager);
	m_pText = new ServerText(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState);
	m_pModeManager			= new ServerModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother, m_pGameTimeManager, m_pShadow, m_pText);

	//ModeManagerSet��Brother�Ȃǂɑ΂���m_ModeManager��n��
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	m_pShadow->ModeManagerSet(m_pModeManager);
	m_pText->ModeManagerSet(m_pModeManager);
	m_pGameTimeManager->ModeManagerSet(m_pModeManager);

	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	
	//����͎����̊��Ⴂ�������̂ł����Ȃ�
	//IN_ADDR inaddr; 				// IP�A�h���X���i�[����\����
	//char szBuf[256]; // �z�X�g��/IP�A�h���X���i�[����z��
	//// WinSock�̏�����
	//WSADATA wsaData;
	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	//// ���[�J���}�V���̃z�X�g�����擾����
	//gethostname(szBuf, (int)sizeof(szBuf));
	//lpHost = gethostbyname(szBuf);
	//for (int i = 0; lpHost->h_addr_list[i]; i++) {
	//	memcpy(&inaddr, lpHost->h_addr_list[i], 4);
	//	strcpy_s(szIP, inet_ntoa(inaddr));
	//}


	DWORD dwID;
	CreateThread(NULL, 0, this->Connect, (LPVOID)this, 0, &dwID);
}


ServerGameScene::~ServerGameScene()
{
	//�摜��uv���̃����[�X
	m_pLibrary->FileInfoRelease();
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->AnimaInfoRelease();


	m_isGameScene = false;

	//�X���b�h�I����҂�����ǉ�����

	m_pisConnect = NULL;
	pFont->Release();

	//�I�u�W�F�N�g
	
	delete m_pModeManager;

	delete m_pText;
	delete m_pShadow;
	delete m_pYoungerBrother;
	delete m_pBrother;
	delete m_pGameTimeManager;
	delete m_pDrawPositionSetter;
	delete m_pCollisionChecker;
	delete m_pMap;
	delete m_pSceneChangeListener;

	m_pLibrary->ReleaseSound(GAME_BGM);
	m_pLibrary->ReleaseTexture(TEX_GAME);
}

SCENE_NUM ServerGameScene::Control()
{
	if (*m_pisConnect == false)
	{

	}
	else
	{
		PadCheck();		//���͂̃`�F�b�N

		m_pModeManager->Control();

		m_pGameTimeManager->Control();

		m_pMap->Control();

		m_pShadow->Control();

		m_pText->Control();

		//�S������������
		//Debug�̃o�O�͂����̂���
		//Release�͍œK������邩����v�̂͂�
		m_pBrother->SwitchOn();
		m_pYoungerBrother->SwitchOn();

		m_pBrother->Control();
		m_pYoungerBrother->Control();
	}
	return m_NextScene;
}

void ServerGameScene::Draw()
{
	if (*m_pisConnect == false)
	{
		CustomVertex waiting[4] =
		{
			{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 0.0 },
			{ 1280.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 0.0 },
			{ 1280.0, 1024.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 1.0 },
			{ 0.0, 1024.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 1.0 }
		};

		m_pLibrary->DrawTexture(CONNECTING_WAIT,waiting);
	}
	else
	{
		m_pShadow->Draw();

		m_pMap->Draw();
		m_pBrother->Draw();
		m_pYoungerBrother->Draw();



		m_pLibrary->StencilTestEnd();
		m_pBrother->UiDraw();
		m_pYoungerBrother->UiDraw();

		m_pText->Draw();


		RECT rect = { 10, 10, 0, 0 };

		pFont->DrawText(NULL, "���̓`�F�b�N", -1, &rect, DT_CALCRECT, NULL);
		pFont->DrawText(NULL, "���̓`�F�b�N", -1, &rect, DT_LEFT | DT_BOTTOM, 0xff00ffff);
	}
}


void ServerGameScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);				//PAD�̏�ԃ`�F�b�N
	
	//PAD�`�F�b�N�����̂ŒʐM����悤�ɂ���
	//isConnect = true;

	//Old�Ɉڂ�
	m_PadOldState[ANALOG_LEFT] =	m_PadState[ANALOG_LEFT];
	m_PadOldState[ANALOG_RIGHT] =	m_PadState[ANALOG_RIGHT];
	m_PadOldState[ANALOG_DOWN] =	m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP] =		m_PadState[ANALOG_UP];

	//�X�e�B�b�N�̏�Ԃ��擾����
	m_PadState[ANALOG_LEFT] = m_pLibrary->GetAnalogState(ANALOG_LEFT, GAMEPAD1);
	m_PadState[ANALOG_RIGHT] = m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
	m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);


	m_ButtonState[0] = m_pLibrary->GetButtonState(GAMEPAD_A,GAMEPAD1);
	m_ButtonState[1] = m_pLibrary->GetButtonState(GAMEPAD_B, GAMEPAD1);

	
}

void ServerGameScene::GetBrotherPos(short* posx, short* posy)
{
	*posx = static_cast<short>(m_pBrother->m_PlayerX);
	*posy = static_cast<short>(m_pBrother->m_PlayerY);
}

void ServerGameScene::SetYoungBrotherPos(short* posx, short* posy)
{
	m_pYoungerBrother->m_PlayerX = *posx;
	m_pYoungerBrother->m_PlayerY = *posy;
}