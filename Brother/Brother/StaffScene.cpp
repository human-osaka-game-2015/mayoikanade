#include "StaffScene.h"
#include "StaffBackGround.h"
#include "Library.h"


StaffScene::StaffScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("StaffTex.csv", STAFF_VERTEXINFO_MAX);
	m_pLibrary->Tex_Load_EX("StaffScene.png", &m_pTexture, 255, 0, 255, 0);

	m_pStaffBackGround = new StaffBackGround(m_pLibrary,m_pTexture);
}

StaffScene::~StaffScene()
{
	delete m_pStaffBackGround;

	m_pTexture->Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->FileInfo_Release();
}

SCENE_NUM StaffScene::Control()
{
	if (m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1) == PAD_PUSH)
	{
		m_NextScene = TITLE_SCENE;
	}

	return m_NextScene;
}

void StaffScene::Draw()
{
	m_pStaffBackGround->Draw();
}

void StaffScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
}
