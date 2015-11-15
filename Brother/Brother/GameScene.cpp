#include "GameScene.h"
#include "Library.h"
#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "YoungerBrother.h"
#include "Brother.h"
#include "Map.h"
#include "CollisionChecker.h"


GameScene::GameScene(Library* pLibrary) :m_pLibrary(pLibrary),m_NextScene(SCENE_NONE)
{
	for (int i = 0; i < PAD_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}

	//GameSceneの画像とcsvの読み込み
	m_pLibrary->m_pUVSetter->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->m_pUVSetter->VertexInfo_Set("tex.csv", VERTEX_INFO);
	m_pLibrary->m_pUVSetter->AnimaInfo_Set("animation.csv", ANIMA_INFO);
	m_pLibrary->m_pTexture->Tex_Load_EX("alpha_main.png", &m_pTexture[0], 255, 0, 255, 0);


	m_pSceneChangeListener = new SceneChangeListener(&m_NextScene);
	m_pMap = new Map(m_pLibrary, m_pTexture[0]);
	m_pCollisionChecker = new CollisionChecker(m_pMap);
	m_pBrother = new Brother(m_pLibrary, m_pTexture[0], m_PadState, m_PadOldState,m_pCollisionChecker);
	m_pYoungerBrother = new YoungerBrother(m_pLibrary, m_pTexture[0], m_PadState, m_PadOldState);		//現状使わない
	m_pModeManager = new ModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother);

	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	
	//Dxfont
	D3DXCreateFont(m_pLibrary->m_pD3DManager->pD3Device, 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	
}

GameScene::~GameScene()
{
	delete m_pModeManager;
	delete m_pYoungerBrother;
	delete m_pBrother;
	delete m_pCollisionChecker;
	delete m_pMap;
	delete m_pSceneChangeListener;
}

SCENE_NUM GameScene::Control()
{
	PadCheck();
	m_pBrother->Control();
	m_pMap->Control();
	return m_NextScene;
}

void GameScene::Draw()
{
	m_pLibrary->m_pD3DManager->Draw_Ready();

	m_pMap->Draw();
	m_pBrother->Draw();

	RECT rect = { 10, 10, 0, 0 };

	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_CALCRECT, NULL);
	pFont->DrawText(NULL, "入力チェック", -1, &rect, DT_LEFT | DT_BOTTOM, 0xffff0000);


	m_pLibrary->m_pD3DManager->Draw_End();


}

int GameScene::GetTime()
{
	return 0;//仮
}

void GameScene::PadCheck()
{
	m_PadOldState[PAD_LEFT] =	m_PadState[PAD_LEFT];
	m_PadOldState[PAD_RIGHT] =	m_PadState[PAD_RIGHT];
	m_PadOldState[PAD_DOWN] =	m_PadState[PAD_DOWN];
	m_PadOldState[PAD_UP] =		m_PadState[PAD_UP];

	m_PadState[PAD_LEFT] =	m_pLibrary->m_pXInput->L_Analog_Left();
	m_PadState[PAD_RIGHT] = m_pLibrary->m_pXInput->L_Analog_Right();
	m_PadState[PAD_DOWN] =	m_pLibrary->m_pXInput->L_Analog_Down();
	m_PadState[PAD_UP] =	m_pLibrary->m_pXInput->L_Analog_Up();

	m_pLibrary->m_pXInput->Check(XINPUT_GAMEPAD_A, GAMEPAD_A);
	m_pLibrary->m_pXInput->Check(XINPUT_GAMEPAD_B, GAMEPAD_B);

}
