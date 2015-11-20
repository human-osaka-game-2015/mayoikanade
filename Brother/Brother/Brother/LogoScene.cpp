#include "LogoScene.h"
#include "LogoBackGround.h"
#include "Library.h"

LogoScene::LogoScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{
	//�t�@�C���̏��͂��������ǂݍ��܂��ɂ��Ƃœǂ񂾂ق��������Ǝv��
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("LogoTex.csv", LOGO_VERTEXINFO_MAX);
	m_pLibrary->LoadTextureEx("LogoScene.png", TEX_LOGO, 255, 0, 255, 0);
	//�A�j���[�V�����͂Ȃ�����K�v�Ȃ�
	
	m_pLogoBackGround = new LogoBackGround(m_pLibrary);
}

LogoScene::~LogoScene()
{
	delete m_pLogoBackGround;

	m_pLibrary->ReleaseTexture(TEX_LOGO);
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->FileInfo_Release();
}

SCENE_NUM LogoScene::Control()
{
	PadCheck();
	if (m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1) == PAD_PUSH)
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
	m_pLibrary->Check(GAMEPAD1);
}
