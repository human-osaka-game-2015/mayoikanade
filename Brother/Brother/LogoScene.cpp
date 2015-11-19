#include "LogoScene.h"
#include "LogoBackGround.h"
#include "Library.h"

LogoScene::LogoScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{
	//ファイルの情報はいちいち読み込まずにもとで読んだほうがいいと思う
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("LogoTex.csv", LOGO_VERTEXINFO_MAX);
	m_pLibrary->Tex_Load_EX("LogoScene.png",&m_pTexture,255,0,255,0);
	//アニメーションはないから必要ない
	
	m_pLogoBackGround = new LogoBackGround(m_pLibrary, m_pTexture);
}

LogoScene::~LogoScene()
{
	delete m_pLogoBackGround;

	m_pTexture->Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->FileInfo_Release();
}

SCENE_NUM LogoScene::Control()
{
	PadCheck();
	if (m_pLibrary->m_pXInput->GetButtonState(GAMEPAD_A, GAMEPAD1) == PAD_PUSH)
	{
		m_NextScene = TITLE_SCENE;
	}

	if (m_pLogoBackGround->Control())
	{
		m_NextScene = TITLE_SCENE;
	}

	return m_NextScene;
}

void LogoScene::Draw()
{
	m_pLogoBackGround->Draw();
}

void LogoScene::PadCheck()
{
	m_pLibrary->m_pXInput->Check(GAMEPAD1);
}
