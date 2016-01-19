#include "Client.h"
#include <Windows.h>
#include "ClientGameScene.h"
#include "Library.h"
#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "ClientYoungerBrother.h"
#include "ClientBrother.h"
#include "Map.h"
#include "CollisionChecker.h"
#include "Text.h"
#include "Shadow.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"


//クライアント
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

	//位置の同期するタイミングをとる。でも多分、使わなくなると思う。
	static int SyncCount = 0;

	//サーバーで送受信する時の配列のデータ内容-------------------------------------------------------------
	// 0 LEFT
	// 1 RIGHT
	// 2 DOWN
	// 3 UP
	// 4 A
	// 5 B
	//-------------------------------------------------------------------------------------------------

	DWORD SyncOld = timeGetTime();
	//DWORD SyncNow;

	timeBeginPeriod(1);

	while (pGameScene->m_isGameScene)
	{
		//SyncNow = timeGetTime();

		//Sleep(1);
		if (pGameScene->isConnect == true/* && SyncNow - SyncOld >= 1000 / 60*/)
		{
			
			for (int i = 0; i < 4; i++)
			{
				if (pGameScene->m_PadState[i] == true)
				{
					pGameScene->CData[i] = 1;
				}
				else
				{
					pGameScene->CData[i] = 0;
				}
			}


			for (int i = 4; i < 6; i++)
			{
				if (pGameScene->m_ButtonState[i - 4] == PAD_PUSH || pGameScene->m_ButtonState[i - 4] == PAD_ON)
				{
					pGameScene->CData[i] = 1;
				}
				else if (pGameScene->m_ButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ButtonState[i - 4] == PAD_OFF)
				{
					pGameScene->CData[i] = 0;
				}
			}
			//位置を同期させるためだけど今は、うまく行ってないので
			//pGameScene->GetYoungBrotherPos(&pGameScene->m_SendData.Yposx,&pGameScene->m_SendData.Yposy);

			//char* sendptr = reinterpret_cast<char*>(&pGameScene->CData);
			BrotherClient.sendData(pGameScene->CData, sizeof(pGameScene->CData));



			//char* recvptr = reinterpret_cast<char*>(&pGameScene->SData);
			BrotherClient.recvData(pGameScene->SData, sizeof(pGameScene->SData));
			//位置を同期させるためだけど今は、うまく行ってないので
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
				if (pGameScene->SData[i] == 1)
				{
					pGameScene->m_ServerPadState[i] = true;
				}
				else
				{
					pGameScene->m_ServerPadState[i] = false;
				}
			}


			//ライブラリの修正にもなるのでいまはこれで
			for (int i = 4; i < 6; i++)
			{
				if (pGameScene->SData[i] == 1)
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
				else if (pGameScene->SData[i] == 0)
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


			ZeroMemory(&pGameScene->CData, sizeof(pGameScene->CData));
			ZeroMemory(&pGameScene->SData, sizeof(pGameScene->SData));
			pGameScene->isConnect = false;
			SyncCount++;
		}
	}
	timeEndPeriod(1);

	ExitThread(TRUE);
}


ClientGameScene::ClientGameScene(Library* pLibrary, HWND hWnd, char* IPadd, bool* pisGameClear) :
Scene(pLibrary), 
m_hWnd(hWnd),
m_pisGameClear(pisGameClear),
m_isGameScene(true),
isConnect(false)
{
	for (int i = 0; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}

	//GameSceneの画像とcsvの読み込み
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("GameTex.csv", GAME_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfoSet("Gameanimation.csv", GAMEANIMA_MAX);
	m_pLibrary->LoadTextureEx("GameScene.png", TEX_GAME, 255, 0, 255, 0);
	m_pLibrary->LoadTextureEx("Ui.png", TEX_UI, 255, 0, 255, 0);
	m_pLibrary->LoadTextureEx("en.png", STENCIL, 255, 0, 255, 255);


	m_pLibrary->SoundLoad("S_G_BGM.wav", GAME_BGM);

	//音声ループ
	m_pLibrary->SoundOperation(GAME_BGM, SOUND_LOOP);


	m_pSceneChangeListener	= new SceneChangeListener(&m_NextScene,m_pisGameClear);
	m_pMap					= new Map(m_pLibrary);
	m_pCollisionChecker		= new CollisionChecker(m_pMap);
	m_pDrawPositionSetter	= new DrawPositionSetter(m_pMap);
	m_pGameTimeManager		= new GameTimeManager(&m_time);
	m_pYoungerBrother		= new ClientYoungerBrother(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager);
	m_pBrother				= new ClientBrother(m_pLibrary, m_ServerPadState, m_ServerPadOldState, m_ServerButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager, m_pYoungerBrother);
	m_pShadow				= new Shadow(m_pLibrary, m_pGameTimeManager);
	m_pText					= new Text(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState);
	
	m_pModeManager = new ModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother, m_pGameTimeManager, m_pShadow, m_pText, m_pisGameClear,m_pMap);

	//ModeManagerSetはBrotherなどに対してm_ModeManagerを渡す
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	m_pShadow->ModeManagerSet(m_pModeManager);
	m_pText->ModeManagerSet(m_pModeManager);
	m_pGameTimeManager->ModeManagerSet(m_pModeManager);

	m_pYoungerBrother->PlayerSet(m_pBrother);

#ifdef _DEBUG
	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	
#endif

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
	//画像のuv情報のリリース
	m_pLibrary->FileInfoRelease();
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->AnimaInfoRelease();


	m_isGameScene = false;

	//スレッド終了を待つ処理を追加する

	Sleep(3000);


#ifdef _DEBUG
	pFont->Release();
#endif

	//オブジェクト
	
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

SCENE_NUM ClientGameScene::Control()
{
	PadCheck();		//入力のチェック

	m_pModeManager->Control();

	m_pGameTimeManager->Control();

	m_pMap->Control();

	m_pShadow->Control();

	m_pText->Control();

	//こいつが犯人
	//Debugの実行して箱を置くときに起きるバグは多分こいつが悪い
	//処理を効率的にすることで何とかなりそう
	//とりあえず今のこいつの処理はひどい
	m_pBrother->SwitchOn();
	m_pYoungerBrother->SwitchOn();


	if (m_pModeManager->m_alpha == 0)
	{
		m_pBrother->Control();
		m_pYoungerBrother->Control();
	}


	
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

	m_pText->Draw();
	//ステージ移動演出
	CustomVertex blackout[4];
	Position m_Pos = { 640, 512, 1280, 1024 };
	m_pLibrary->xySet(m_Pos, blackout);
	m_pLibrary->MakeVertex(BLACKOUT, blackout);

	for (int i = 0; i < 4; i++)
	{
		blackout[i].color = D3DCOLOR_ARGB(m_pModeManager->m_alpha, 0, 0, 0);
	}
	m_pLibrary->DrawTexture(TEX_GAME, blackout);


#ifdef _DEBUG

	RECT rect = { 10, 10, 0, 0 };

	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_CALCRECT, NULL);
	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_LEFT | DT_BOTTOM, 0xff00ffff);
#endif

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
