#include "Client.h"
#include <Windows.h>
#include "ClientGameScene.h"
#include "Library.h"
#include "ClientModeManager.h"
#include "SceneChangeListener.h"
#include "ClientYoungerBrother.h"
#include "ClientBrother.h"
#include "ClientMap.h"
#include "ClientCollisionChecker.h"
#include "ClientText.h"
#include "ClientShadow.h"
#include "ClientGameTimeManager.h"
#include "ClientDrawPositionSetter.h"


//�N���C�A���g
DWORD WINAPI ClientGameScene::Connect(LPVOID Gamemain)
{
	GameThread* p_GameThread = static_cast<GameThread*>(Gamemain);
	ClientGameScene* pGameScene = static_cast<ClientGameScene*>(p_GameThread->pGameScene);
	Client BrotherClient("8000");
	char IP[16];

	for (int i = 0; i < 16; i++)
	{
		IP[i] = p_GameThread->portnum[i];
	}
	BrotherClient.serverConnect(IP);

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

	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	while (pGameScene->m_isGameScene)
	{
		SyncNow = timeGetTime();

		Sleep(1);
		if (pGameScene->isConnect == true && SyncNow - SyncOld >= 1000 / 60)
		{
			
			for (int i = 0; i < 4; i++)
			{
				if (pGameScene->m_PadState[i] == true)
				{
					pGameScene->m_SendData.CData[i] = 1;
				}
				else
				{
					pGameScene->m_SendData.CData[i] = 0;
				}
			}


			for (int i = 4; i < 6; i++)
			{
				if (pGameScene->m_ButtonState[i - 4] == PAD_PUSH || pGameScene->m_ButtonState[i - 4] == PAD_ON)
				{
					pGameScene->m_SendData.CData[i] = 1;
				}
				else if (pGameScene->m_ButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ButtonState[i - 4] == PAD_OFF)
				{
					pGameScene->m_SendData.CData[i] = 0;
				}
			}
			//�ʒu�𓯊������邽�߂����Ǎ��́A���܂��s���ĂȂ��̂�
			//pGameScene->GetYoungBrotherPos(&pGameScene->m_SendData.Yposx,&pGameScene->m_SendData.Yposy);

			char* sendptr = reinterpret_cast<char*>(&pGameScene->m_SendData);
			BrotherClient.sendData(sendptr, sizeof(pGameScene->m_SendData));



			char* recvptr = reinterpret_cast<char*>(&pGameScene->m_RecvData);
			BrotherClient.recvData(recvptr, sizeof(pGameScene->m_RecvData));
			//�ʒu�𓯊������邽�߂����Ǎ��́A���܂��s���ĂȂ��̂�
			//if (SyncCount % 120 == 0)
			//{
			//	pGameScene->SetBrotherPos(&pGameScene->m_RecvData.Bposx, &pGameScene->m_RecvData.Bposy);
			//}


			pGameScene->m_ServerPadOldState[ANALOG_LEFT] = pGameScene->m_ServerPadState[ANALOG_LEFT];
			pGameScene->m_ServerPadOldState[ANALOG_RIGHT] = pGameScene->m_ServerPadState[ANALOG_RIGHT];
			pGameScene->m_ServerPadOldState[ANALOG_DOWN] = pGameScene->m_ServerPadState[ANALOG_DOWN];
			pGameScene->m_ServerPadOldState[ANALOG_UP] = pGameScene->m_ServerPadState[ANALOG_UP];

			for (int i = 0; i < 4; i++)
			{
				if (pGameScene->m_RecvData.SData[i] == 1)
				{
					pGameScene->m_ServerPadState[i] = true;
				}
				else
				{
					pGameScene->m_ServerPadState[i] = false;
				}
			}


			//���C�u�����̏C���ɂ��Ȃ�̂ł��܂͂����
			for (int i = 4; i < 6; i++)
			{
				if (pGameScene->m_RecvData.SData[i] == 1)
				{
					if (pGameScene->m_ServerButtonState[i - 4] == PAD_PUSH || pGameScene->m_ServerButtonState[i - 4] == PAD_ON)
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_ON;
					}
					else
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_PUSH;
					}
				}
				else if (pGameScene->m_RecvData.SData[i] == 0)
				{
					if (pGameScene->m_ServerButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ServerButtonState[i - 4] == PAD_OFF)
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_OFF;
					}
					else
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_RELEASE;
					}
				}
			}


			ZeroMemory(&pGameScene->m_SendData, sizeof(pGameScene->m_SendData));
			ZeroMemory(&pGameScene->m_RecvData, sizeof(pGameScene->m_RecvData));
			pGameScene->isConnect = false;
			SyncCount++;
		}
	}
	timeEndPeriod(1);

	ExitThread(TRUE);
}


ClientGameScene::ClientGameScene(Library* pLibrary, HWND hWnd,char* IPadd) :
Scene(pLibrary), 
m_hWnd(hWnd),
m_isGameScene(true),
isConnect(false)
{
	for (int i = 0; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}

	//GameScene�̉摜��csv�̓ǂݍ���
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("GameTex.csv", GAME_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfo_Set("Gameanimation.csv", GAMEANIMA_MAX);
	m_pLibrary->LoadTextureEx("GameScene.png", TEX_GAME, 255, 0, 255, 0);
	m_pLibrary->LoadTextureEx("en.png", STENCIL, 255, 0, 255, 255);


	m_pLibrary->SoundLoad("S_G_BGM.wav", GAME_BGM);

	//�������[�v
	m_pLibrary->Sound_Operation(GAME_BGM, SOUND_LOOP);


	m_pSceneChangeListener	= new SceneChangeListener(&m_NextScene);
	m_pMap = new ClientMap(m_pLibrary);
	m_pCollisionChecker = new ClientCollisionChecker(m_pMap);
	m_pDrawPositionSetter = new ClientDrawPositionSetter(m_pMap);
	m_pGameTimeManager = new ClientGameTimeManager(&m_time);
	m_pYoungerBrother = new ClientYoungerBrother(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager);
	m_pBrother = new ClientBrother(m_pLibrary, m_ServerPadState, m_ServerPadOldState, m_ServerButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager, m_pYoungerBrother);
	m_pShadow = new ClientShadow(m_pLibrary, m_pGameTimeManager);
	m_pText = new ClientText(m_pLibrary);
	
	m_pModeManager = new ClientModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother, m_pGameTimeManager, m_pShadow);

	//ModeManagerSet��Brother�Ȃǂɑ΂���m_ModeManager��n��
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	m_pShadow->ModeManagerSet(m_pModeManager);
	m_pText->ModeManagerSet(m_pModeManager);
	m_pGameTimeManager->ModeManagerSet(m_pModeManager);

	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	

	DWORD dwID;
	Gamemain.pGameScene = this;
	for (int a = 0; a < 16; a++)
	{
		Gamemain.portnum[a] = IPadd[a];
	}

	CreateThread(NULL, 0, Connect, (LPVOID)&Gamemain, 0, &dwID);
}

ClientGameScene::~ClientGameScene()
{
	//�摜��uv���̃����[�X
	m_pLibrary->FileInfo_Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->AnimaInfo_Release();


	m_isGameScene = false;

	//�X���b�h�I����҂�����ǉ�����

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

	m_pLibrary->SoundRelease(GAME_BGM);
	m_pLibrary->ReleaseTexture(TEX_GAME);
}

SCENE_NUM ClientGameScene::Control()
{
	PadCheck();		//���͂̃`�F�b�N

	m_pModeManager->Control();

	m_pGameTimeManager->Control();

	m_pMap->Control();

	m_pShadow->Control();

	
	//�������Ɛl
	//Debug�̎��s���Ĕ���u���Ƃ��ɋN����o�O�͑�������������
	//�����������I�ɂ��邱�Ƃŉ��Ƃ��Ȃ肻��
	//�Ƃ肠�������̂����̏����͂Ђǂ�
	m_pBrother->SwitchOn();
	m_pYoungerBrother->SwitchOn();


	m_pBrother->Control();
	m_pYoungerBrother->Control();


	
	return m_NextScene;
}

void ClientGameScene::Draw()
{

	m_pShadow->Draw();

	m_pMap->Draw();
	m_pBrother->Draw();
	m_pYoungerBrother->Draw();



	m_pLibrary->StencilTestEnd();
	m_pBrother->UiDraw();
	m_pYoungerBrother->UiDraw();




	RECT rect = { 10, 10, 0, 0 };

	pFont->DrawText(NULL, "���̓`�F�b�N", -1, &rect, DT_CALCRECT, NULL);
	pFont->DrawText(NULL, "���̓`�F�b�N", -1, &rect, DT_LEFT | DT_BOTTOM, 0xff00ffff);


}


void ClientGameScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	isConnect = true;

	m_PadOldState[ANALOG_LEFT] =	m_PadState[ANALOG_LEFT];
	m_PadOldState[ANALOG_RIGHT] =	m_PadState[ANALOG_RIGHT];
	m_PadOldState[ANALOG_DOWN] =	m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP] =		m_PadState[ANALOG_UP];

	m_PadState[ANALOG_LEFT] = m_pLibrary->GetAnalogState(ANALOG_LEFT, GAMEPAD1);
	m_PadState[ANALOG_RIGHT] = m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
	m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);


	m_ButtonState[0] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
	m_ButtonState[1] = m_pLibrary->GetButtonState(GAMEPAD_B, GAMEPAD1);


	
}

void ClientGameScene::GetYoungBrotherPos(short* posx, short* posy)
{
	*posx = static_cast<short>(m_pYoungerBrother->m_PlayerX);
	*posy = static_cast<short>(m_pYoungerBrother->m_PlayerY);
}

void ClientGameScene::SetBrotherPos(short* posx, short* posy)
{
	m_pBrother->m_PlayerX = *posx;
	m_pBrother->m_PlayerY = *posy;
}