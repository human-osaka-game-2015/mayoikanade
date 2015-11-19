#include "TitleScene.h"
#include "Library.h"
#include "TitleBackGround.h"
#include "TitleName.h"
#include "TitleTimeManager.h"
#include "TitleSelectManager.h"

TitleScene::TitleScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("TitleTex.csv", TITLE_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfo_Set("TitleAnimation.csv", TITLEANIMA_ID_MAX);
	m_pLibrary->Tex_Load_EX("TitleScene.png", &m_pTexture, 255, 0, 255, 0);


	m_pTitleBackGround = new TitleBackGround(m_pLibrary, m_pTexture);
	m_pTitleName = new TitleName(m_pLibrary, m_pTexture);
	m_pTitleSelectManager = new TitleSelectManager(m_pLibrary, m_pTexture,m_PadState,m_PadOldState);
	m_pTitleTimeManager = new TitleTimeManager(m_pLibrary,m_pTexture);
}

TitleScene::~TitleScene()
{
	delete m_pTitleTimeManager;
	delete m_pTitleName;
	delete m_pTitleSelectManager;
	delete m_pTitleBackGround;

	m_pTexture->Release();
	m_pLibrary->AnimaInfo_Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->FileInfo_Release();

}

void TitleScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_PadOldState[ANALOG_LEFT] = m_PadState[ANALOG_LEFT];
	m_PadOldState[ANALOG_RIGHT] = m_PadState[ANALOG_RIGHT];
	m_PadOldState[ANALOG_DOWN] = m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP] = m_PadState[ANALOG_UP];

	m_PadState[ANALOG_LEFT] = m_pLibrary->GetAnalogState(ANALOG_LEFT,GAMEPAD1);
	m_PadState[ANALOG_RIGHT] = m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
	m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);
}


SCENE_NUM TitleScene::Control()
{
	PadCheck();

	//TitleManagerのコントロール
	//一定時間経過でフェードアウトしきったらtrueを返してくる。
	if (m_pTitleTimeManager->Control())
	{
		m_NextScene = LOGO_SCENE;
	}
	else
	{
		//返ってきた返り値により次のシーンを判断する
		switch (m_pTitleSelectManager->Control())
		{
		case GAME_START:
			m_NextScene = GAME_SCENE;

			break;
		case GAME_END:
			m_NextScene = END_SCENE;

			break;
		case GAME_STAFF:
			m_NextScene = STAFF_SCENE;

			break;
		case TITLESELECT_NONE:
			m_NextScene = SCENE_NONE;

			break;
		}
	}

	return m_NextScene;
}

void TitleScene::Draw()
{
	m_pTitleBackGround->Draw();
	m_pTitleName->Draw();
	m_pTitleSelectManager->Draw();
	m_pTitleTimeManager->Draw();
}