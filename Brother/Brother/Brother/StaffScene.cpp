#include "StaffScene.h"
#include "StaffBackGround.h"
#include "Library.h"


StaffScene::StaffScene(Library* pLibrary) :Scene(pLibrary)
{
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("StaffTex.csv", STAFF_VERTEXINFO_MAX);
	m_pLibrary->LoadTextureEx("StaffScene.png", TEX_STAFF, 255, 0, 255, 0);

	m_pStaffBackGround = new StaffBackGround(m_pLibrary);
}

StaffScene::~StaffScene()
{
	delete m_pStaffBackGround;

	m_pLibrary->ReleaseTexture(TEX_STAFF);
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->FileInfo_Release();
}

SCENE_NUM StaffScene::Control()
{
	PadCheck();
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
