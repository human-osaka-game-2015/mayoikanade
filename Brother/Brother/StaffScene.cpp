#include "StaffScene.h"
#include "StaffBackGround.h"
#include "Library.h"


StaffScene::StaffScene(Library* pLibrary) :Scene(pLibrary)
{
	//time‚Ì‰Šú‰»
	m_time = 0;

	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("StaffTex.csv", STAFF_VERTEXINFO_MAX);
	m_pLibrary->LoadTextureEx("StaffScene.png", TEX_STAFF, 255, 0, 255, 0);

	m_pStaffBackGround = new StaffBackGround(m_pLibrary);
}

StaffScene::~StaffScene()
{
	delete m_pStaffBackGround;
	
	m_pLibrary->ReleaseTexture(TEX_STAFF);
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
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
