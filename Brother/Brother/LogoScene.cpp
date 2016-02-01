#include "LogoScene.h"
#include "LogoBackGround.h"
#include "Library.h"

/**
 * LogoSceneのコンストラクタ
 * @param[in] pLibrary
 */
LogoScene::LogoScene(Library* pLibrary) :
Scene(pLibrary)
{
	//csvファイルの読み込み
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("LogoTex.csv", LOGO_VERTEXINFO_MAX);
	
	//画像の読み込み
	m_pLibrary->LoadTextureEx("LogoScene.png", TEX_LOGO, COLORMAX, COLORMIN, COLORMAX, COLORMIN);

	//ロゴシーン内オブジェクトの生成
	m_pLogoBackGround = new LogoBackGround(m_pLibrary);
}

/**
 * LogoSceneのデストラクタ
 */
LogoScene::~LogoScene()
{
	//オブジェクトの解放処理
	delete m_pLogoBackGround;

	//ファイルの読み込み
	m_pLibrary->ReleaseTexture(TEX_LOGO);
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

/**
 * LogoSceneのコントロール関数
 * @return 遷移先のシーン
 */
SCENE_NUM LogoScene::Control()
{
	PadCheck();

	if (m_ButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		m_NextScene = OPENING_SCENE;
	}

	if (m_pLogoBackGround->Control())
	{
		m_NextScene = OPENING_SCENE;
	}

	return m_NextScene;
}

/**
 * LogoSceneの描画関数
 */
void LogoScene::Draw()
{
	m_pLogoBackGround->Draw();
}

/**
 * LogoSceneでのGamePadチェック関数
 */
void LogoScene::PadCheck()
{
	//1Pのコントローラーの状態チェック
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}
