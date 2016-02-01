#include "StaffScene.h"
#include "StaffBackGround.h"
#include "Library.h"


/**
 * StaffSceneクラスのコンストラクタ
 * @param[in] pLibrary	ライブラリクラス
 */
StaffScene::StaffScene(Library* pLibrary) :
Scene(pLibrary)
{
	//ファイルの読み込み
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("StaffTex.csv", STAFF_VERTEXINFO_MAX);
	m_pLibrary->LoadTextureEx("StaffScene.png", TEX_STAFF, 255, 0, 255, 0);

	//オブジェクトの生成
	m_pStaffBackGround = new StaffBackGround(m_pLibrary);
}

/**
 * StaffSceneクラスのデストラクタ
 */
StaffScene::~StaffScene()
{
	delete m_pStaffBackGround;
	
	m_pLibrary->ReleaseTexture(TEX_STAFF);
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

/**
 * StaffSceneクラスのコンストラクタ
 * @return 遷移先のシーン 
 */
SCENE_NUM StaffScene::Control()
{
	PadCheck();
	if (m_ButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		m_NextScene = TITLE_SCENE;
	}

	return m_NextScene;
}

/**
 * StaffSceneクラスの描画
 */
void StaffScene::Draw()
{
	m_pStaffBackGround->Draw();
}

/**
 * StaffSceneのGamePadのチェック関数
 */
void StaffScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}

