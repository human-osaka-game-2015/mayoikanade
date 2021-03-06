#include "Server.h"

#include "ServerGameScene.h"
#include "Library.h"
#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "ServerYoungerBrother.h"
#include "ServerBrother.h"
#include "Map.h"
#include "CollisionChecker.h"
#include "Text.h"
#include "Shadow.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "Mutex.h"

//サーバー
DWORD WINAPI ServerGameScene::Connect(LPVOID vpGameScene)
{
	ServerGameScene* pGameScene = static_cast<ServerGameScene*>(vpGameScene);
	Server BrotherServer("51234");

	ZeroMemory(pGameScene->CData, sizeof(pGameScene->CData));
	ZeroMemory(pGameScene->SData, sizeof(pGameScene->SData));

	BrotherServer.Clientlisten();

	 
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

	*pGameScene->m_pisConnect = true;
	DWORD SyncOld = timeGetTime();
	//DWORD SyncNow;

	timeBeginPeriod(1);

	while (pGameScene->m_isGameScene)
	{
		//SyncNow = timeGetTime();
		//
		//Sleep(1);
		if (pGameScene->m_pisConnect != NULL  && pGameScene->m_KeyCheckOK == true)
		{
			pGameScene->m_pMutex->GetMutexHwnd();
			pGameScene->m_pMutex->WaitMutex();
			bool isConnect = *pGameScene->m_pisConnect;
			if (isConnect == true)
			{
				//char* recvptr = reinterpret_cast<char*>(&pGameScene->m_RecvData);
				BrotherServer.recvData(pGameScene->CData, sizeof(pGameScene->CData));
				//位置を同期させるためだけど今は、うまく行ってないので
				//if (SyncCount % 120 == 0)
				//{
				//	pGameScene->SetYoungBrotherPos(&pGameScene->m_RecvData.Yposx, &pGameScene->m_RecvData.Yposy);
				//}
				for (int i = 0; i < 4; i++)
				{
					if (pGameScene->CData[i] == 1)
					{
						pGameScene->m_ClientPadState[i] = true;
					}
					else
					{
						pGameScene->m_ClientPadState[i] = false;
					}
				}


				//クライアントのスティックのデータを移す
				pGameScene->m_ClientPadOldState[ANALOG_LEFT] = pGameScene->m_ClientPadState[ANALOG_LEFT];
				pGameScene->m_ClientPadOldState[ANALOG_RIGHT] = pGameScene->m_ClientPadState[ANALOG_RIGHT];
				pGameScene->m_ClientPadOldState[ANALOG_DOWN] = pGameScene->m_ClientPadState[ANALOG_DOWN];
				pGameScene->m_ClientPadOldState[ANALOG_UP] = pGameScene->m_ClientPadState[ANALOG_UP];

				//ライブラリの修正にもなるのでいまはこれで
				for (int i = 4; i < 6; i++)
				{
					if (pGameScene->CData[i] == 1)
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
					else if (pGameScene->CData[i] == 0)
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


				//サーバー側データを詰める
				for (int i = 0; i < 4; i++)
				{
					if (pGameScene->m_PadState[i] == true)
					{
						pGameScene->SData[i] = 1;
					}
					else
					{
						pGameScene->SData[i] = 0;
					}
				}

				for (int i = 4; i < 6; i++)
				{
					if (pGameScene->m_ButtonState[i - 4] == PAD_PUSH || pGameScene->m_ButtonState[i - 4] == PAD_ON)
					{
						pGameScene->SData[i] = 1;
					}
					else if (pGameScene->m_ButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ButtonState[i - 4] == PAD_OFF)
					{
						pGameScene->SData[i] = 0;
					}
				}
				//位置を同期させるためだけど今は、うまく行ってないので
				//pGameScene->GetBrotherPos(&pGameScene->m_SendData.Bposx, &pGameScene->m_SendData.Bposy);
				//char* sendptr = reinterpret_cast<char*>(&pGameScene->m_SendData);
				BrotherServer.sendData(pGameScene->SData, sizeof(pGameScene->SData));

				ZeroMemory(pGameScene->CData, sizeof(pGameScene->CData));
				ZeroMemory(pGameScene->SData, sizeof(pGameScene->SData));

				//*pGameScene->m_pisConnect = false;
			}
			pGameScene->m_KeyCheckOK = false;
			pGameScene->m_RecvSend = true;
			pGameScene->m_pMutex->MutexRelease();
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
m_pisConnect(&m_isConnect),
m_KeyCheckOK(false),
m_RecvSend(false)
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
	m_pLibrary->LoadTextureEx("ConnectingWait.png", CONNECTING_WAIT, 255, 0, 255, 255);
	m_pLibrary->LoadTextureEx("en.png", STENCIL, 255, 0, 255, 255);

	m_pLibrary->SoundLoad("S_G_BGM.wav", GAME_BGM);
	m_pLibrary->SoundLoad("se_maoudamashii_se_switch01.wav", GAME_SWITCH01);

	//音声ループ
	m_pLibrary->SoundOperation(GAME_BGM, SOUND_LOOP);

	m_pSceneChangeListener	= new SceneChangeListener(&m_NextScene,m_pisGameClear);
	m_pMap					= new Map(m_pLibrary);
	m_pCollisionChecker		= new CollisionChecker(m_pMap);
	m_pDrawPositionSetter	= new DrawPositionSetter(m_pMap);
	m_pGameTimeManager		= new GameTimeManager(&m_time);
	m_pBrother				= new ServerBrother(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager);
	m_pYoungerBrother		= new ServerYoungerBrother(m_pLibrary, m_ClientPadState, m_ClientPadOldState, m_ClientButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager, m_pBrother);
	m_pShadow				= new Shadow(m_pLibrary, m_pGameTimeManager);
	m_pText					= new Text(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState);
	m_pModeManager			= new ModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother, m_pGameTimeManager, m_pShadow, m_pText,m_pisGameClear,m_pMap);
	m_pMutex = new Mutex("Server");

	//ModeManagerSetはBrotherなどに対してm_ModeManagerを渡す
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	m_pShadow->ModeManagerSet(m_pModeManager);
	m_pText->ModeManagerSet(m_pModeManager);
	m_pGameTimeManager->ModeManagerSet(m_pModeManager);

	m_pBrother->PlayerSet(m_pYoungerBrother);

#ifdef _DEBUG
	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
#endif



	DWORD dwID;
	CreateThread(NULL, 0, this->Connect, (LPVOID)this, 0, &dwID);
}


ServerGameScene::~ServerGameScene()
{
	//画像のuv情報のリリース
	m_pLibrary->FileInfoRelease();
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->AnimaInfoRelease();


	m_isGameScene = false;

	//スレッド終了を待つ処理を追加する

	m_pisConnect = NULL;
	Sleep(5000);

#ifdef _DEBUG
	pFont->Release();
#endif

	//オブジェクト
	delete m_pMutex;
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
		m_pMutex->GetMutexHwnd();
		m_pMutex->WaitMutex();
	if (*m_pisConnect == false)
	{

	}
	else
	{
		if (m_KeyCheckOK == false)
		{
			PadCheck();		//入力のチェック
			m_KeyCheckOK = true;
		}

		m_pModeManager->Control();

		m_pGameTimeManager->Control();

		m_pMap->Control();

		m_pShadow->Control();

		m_pText->Control();

		//全部こいつが悪い
		//Debugのバグはこいつのせい
		//Releaseは最適化されるから大丈夫のはず
		m_pBrother->SwitchOn();
		m_pYoungerBrother->SwitchOn();
		
		if (m_RecvSend)
		{
			if (m_pModeManager->m_alpha == 0)
			{
				m_pBrother->Control();
				m_pYoungerBrother->Control();
			}
			m_RecvSend = false;
		}
	}
		m_pMutex->MutexRelease();
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
}


void ServerGameScene::PadCheck()
{
		m_pLibrary->Check(GAMEPAD1);				//PADの状態チェック
	
		//PADチェックしたので通信するようにする
		//isConnect = true;

		//Oldに移す
		m_PadOldState[ANALOG_LEFT] =	m_PadState[ANALOG_LEFT];
		m_PadOldState[ANALOG_RIGHT] =	m_PadState[ANALOG_RIGHT];
		m_PadOldState[ANALOG_DOWN] =	m_PadState[ANALOG_DOWN];
		m_PadOldState[ANALOG_UP] =		m_PadState[ANALOG_UP];

		//スティックの状態を取得する
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