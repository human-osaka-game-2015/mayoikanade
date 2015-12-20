#include "Server.h"

#include "GameScene.h"
#include "Library.h"
#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "YoungerBrother.h"
#include "Brother.h"
#include "Map.h"
#include "CollisionChecker.h"
#include "Text.h"
#include "Shadow.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"


//サーバー
DWORD WINAPI GameScene::Connect(LPVOID vpGameScene)
{
	GameScene* pGameScene = static_cast<GameScene*>(vpGameScene);
	Server BrotherServer("8000");

	ZeroMemory(pGameScene->CData, sizeof(pGameScene->CData));
	ZeroMemory(pGameScene->SData, sizeof(pGameScene->SData));

	BrotherServer.Clientlisten();


	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;
	timeBeginPeriod(1);


	while (pGameScene->m_isGameScene)
	{
		if (pGameScene->isConnect == true)
		{

			/*SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)
			{


			SyncOld = SyncNow;
			}*/


			BrotherServer.recvData(pGameScene->CData, sizeof(pGameScene->CData));

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


			BrotherServer.sendData(pGameScene->SData, sizeof(pGameScene->SData));


			ZeroMemory(pGameScene->CData, sizeof(pGameScene->CData));
			ZeroMemory(pGameScene->SData, sizeof(pGameScene->SData));

		}
	}

	timeEndPeriod(1);
	ExitThread(TRUE);
}


GameScene::GameScene(Library* pLibrary, HWND hWnd) :
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

	//GameSceneの画像とcsvの読み込み
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("GameTex.csv", GAME_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfo_Set("Gameanimation.csv", GAMEANIMA_MAX);
	m_pLibrary->LoadTextureEx("GameScene.png", TEX_GAME, 255, 0, 255, 0);
	m_pLibrary->LoadTextureEx("en.png", STENCIL, 255, 0, 255, 255);


	m_pLibrary->SoundLoad("S_G_BGM.wav", GAME_BGM);

	//音声ループ
	m_pLibrary->Sound_Operation(GAME_BGM, SOUND_LOOP);

	m_pSceneChangeListener	= new SceneChangeListener(&m_NextScene);
	m_pMap					= new Map(m_pLibrary);
	m_pCollisionChecker		= new CollisionChecker(m_pMap);
	m_pDrawPositionSetter	= new DrawPositionSetter(m_pMap);
	m_pGameTimeManager		= new GameTimeManager(&m_time); 
	m_pBrother				= new Brother(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager);
	m_pYoungerBrother		= new YoungerBrother(m_pLibrary, m_ClientPadState, m_ClientPadOldState,m_ClientButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager,m_pBrother);
	m_pShadow				= new Shadow(m_pLibrary,m_pGameTimeManager);
	m_pText					= new Text(m_pLibrary);
	
	m_pModeManager			= new ModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother,m_pGameTimeManager,m_pShadow);

	//ModeManagerSetはBrotherなどに対してm_ModeManagerを渡す
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	m_pShadow->ModeManagerSet(m_pModeManager);
	m_pText->ModeManagerSet(m_pModeManager);
	m_pGameTimeManager->ModeManagerSet(m_pModeManager);

	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	
	

	DWORD dwID;
	CreateThread(NULL, 0, Connect, (LPVOID)this, 0, &dwID);
}

GameScene::~GameScene()
{
	//画像のuv情報のリリース
	m_pLibrary->FileInfo_Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->AnimaInfo_Release();


	m_isGameScene = false;

	//スレッド終了を待つ処理を追加する


	pFont->Release();

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

	m_pLibrary->SoundRelease(GAME_BGM);
	m_pLibrary->ReleaseTexture(TEX_GAME);
}

SCENE_NUM GameScene::Control()
{
	PadCheck();		//入力のチェック

	m_pModeManager->Control();

	m_pGameTimeManager->Control();

	m_pMap->Control();

	m_pShadow->Control();

	//全部こいつが悪い
	//Debugのバグはこいつのせい
	//Releaseは最適化されるから大丈夫のはず
	m_pBrother->SwitchOn();
	m_pYoungerBrother->SwitchOn();
	
	m_pBrother->Control();
	m_pYoungerBrother->Control();


	
	return m_NextScene;
}

void GameScene::Draw()
{

	m_pShadow->Draw();

	m_pMap->Draw();
	m_pBrother->Draw();
	m_pYoungerBrother->Draw();



	m_pLibrary->StencilTestEnd();
	m_pBrother->UiDraw();
	m_pYoungerBrother->UiDraw();




	RECT rect = { 10, 10, 0, 0 };

	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_CALCRECT, NULL);
	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_LEFT | DT_BOTTOM, 0xff00ffff);


}


void GameScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);				//PADの状態チェック
	
	//PADチェックしたので通信するようにする
	isConnect = true;

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

	
	//クライアントのスティックのデータを移す
	m_ClientPadOldState[ANALOG_LEFT] = m_ClientPadState[ANALOG_LEFT];
	m_ClientPadOldState[ANALOG_RIGHT] = m_ClientPadState[ANALOG_RIGHT];
	m_ClientPadOldState[ANALOG_DOWN] = m_ClientPadState[ANALOG_DOWN];
	m_ClientPadOldState[ANALOG_UP] = m_ClientPadState[ANALOG_UP];


	


}
