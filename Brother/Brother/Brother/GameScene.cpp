#include "GameScene.h"
#include "Library.h"
#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "YoungerBrother.h"
#include "Brother.h"
#include "Map.h"
#include "CollisionChecker.h"


GameScene::GameScene(Library* pLibrary) :Scene(pLibrary)
{
	for (int i = 0; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}

	//GameSceneの画像とcsvの読み込み
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("GameTex.csv", GAME_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfo_Set("Gameanimation.csv", GAME_ANIMA_INFO);
	m_pLibrary->LoadTextureEx("GameScene.png", TEX_GAME, 255, 0, 255, 0);



	m_pSceneChangeListener = new SceneChangeListener(&m_NextScene);
	m_pMap = new Map(m_pLibrary);
	m_pCollisionChecker = new CollisionChecker(m_pMap);
	m_pBrother = new Brother(m_pLibrary, m_PadState, m_PadOldState,m_pCollisionChecker);
	m_pYoungerBrother = new YoungerBrother(m_pLibrary, m_PadState, m_PadOldState);
	m_pModeManager = new ModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother);

	//ModeManagerSetはBrotherなどに対してm_ModeManagerを渡す
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	
	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	
}

GameScene::~GameScene()
{
	m_pLibrary->FileInfo_Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->AnimaInfo_Release();
	delete m_pModeManager;
	delete m_pYoungerBrother;
	delete m_pBrother;
	delete m_pCollisionChecker;
	delete m_pMap;
	delete m_pSceneChangeListener;

	m_pLibrary->ReleaseTexture(TEX_GAME);
}

SCENE_NUM GameScene::Control()
{
	PadCheck();		//入力のチェック

	m_pBrother->Control();

	m_pMap->Control();
	
	return m_NextScene;
}

void GameScene::Draw()
{

	m_pMap->Draw();
	m_pBrother->Draw();

	RECT rect = { 10, 10, 0, 0 };

	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_CALCRECT, NULL);
	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_LEFT | DT_BOTTOM, 0xffff0000);

}

int GameScene::GetTime()
{
	return 0;//仮
}

void GameScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);

	m_PadOldState[ANALOG_LEFT] =	m_PadState[ANALOG_LEFT];
	m_PadOldState[ANALOG_RIGHT] =	m_PadState[ANALOG_RIGHT];
	m_PadOldState[ANALOG_DOWN] =	m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP] =		m_PadState[ANALOG_UP];

	m_PadState[ANALOG_LEFT] = m_pLibrary->GetAnalogState(ANALOG_LEFT, GAMEPAD1);
	m_PadState[ANALOG_RIGHT] = m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
	m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);
}
