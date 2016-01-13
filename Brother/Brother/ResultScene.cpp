#include "ResultScene.h"
#include "ResultBackGround.h"
#include "ResultClock.h"
#include "ResultText.h"



ResultScene::ResultScene(Library* pLibrary, bool isGameClear) :
Scene(pLibrary),
m_isGameClear(isGameClear)
{
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);

	if (m_isGameClear == true)
	{
		m_pLibrary->VertexInfoSet("GameClear.csv", GAMECLEAR_VERTEXINFO_MAX);
		m_pLibrary->LoadTextureEx("GameClear.png", TEX_GAMECLEAR, 255, 0, 255, 0);
	}
	else
	{
		m_pLibrary->VertexInfoSet("GameOver.csv", GAMEOVER_VERTEXINFO_MAX);
		m_pLibrary->LoadTextureEx("GameOver.png", TEX_GAMEOVER, 255, 0, 255, 0);
	}

	m_pResultBackGround = new ResultBackGround(m_pLibrary, m_isGameClear);
	m_pResultClock = new ResultClock(m_pLibrary, m_isGameClear, m_time);
	m_pResultText = new ResultText(m_pLibrary, m_isGameClear);
	
	m_NextScene = SCENE_NONE;

}

ResultScene::~ResultScene()
{
	delete m_pResultText;
	delete m_pResultClock;
	delete m_pResultBackGround;

	if (m_isGameClear == true)
	{
		m_pLibrary->ReleaseTexture(TEX_GAMECLEAR);
	}
	else
	{
		m_pLibrary->ReleaseTexture(TEX_GAMEOVER);
	}

	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

SCENE_NUM ResultScene::Control()
{
	PadCheck();

	m_pResultBackGround->Control();
	m_pResultClock->Control();
	m_pResultText->Control();

	if (m_ButtonState[0] == PAD_PUSH)
	{
		m_NextScene = LOGO_SCENE;
	}

	return m_NextScene;
}

void ResultScene::Draw()
{
	m_pResultBackGround->Draw();
	m_pResultText->Draw();
	m_pResultClock->Draw();
}

void ResultScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[0] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}
