#include "ResultScene.h"
#include "ResultBackGround.h"
#include "ResultClock.h"
#include "ResultText.h"



/**
 * ResultSceneクラスのコンストラクタ
 * @param[in] pLibrary	ライブラリクラス
 * @param[in] isGameClear ゲームクリアしたかのフラグ
 */
ResultScene::ResultScene(Library* pLibrary, bool isGameClear) :
Scene(pLibrary),
m_isGameClear(isGameClear)
{

	//ファイルの読み込み
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	
	//ゲームクリアかゲームオーバーによって読み込むファイルを変更
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

	//オブジェクトの生成
	m_pResultBackGround = new ResultBackGround(m_pLibrary, m_isGameClear);
	m_pResultClock = new ResultClock(m_pLibrary, m_isGameClear, m_time);
	m_pResultText = new ResultText(m_pLibrary, m_isGameClear);
	
	//遷移先のシーンはNONEに初期化
	m_NextScene = SCENE_NONE;
}


/**
 * ResultSceneクラスのデストラクタ
 */
ResultScene::~ResultScene()
{
	//オブジェクトの破棄
	delete m_pResultText;
	delete m_pResultClock;
	delete m_pResultBackGround;

	//画像の解放
	if (m_isGameClear == true)
	{
		m_pLibrary->ReleaseTexture(TEX_GAMECLEAR);
	}
	else
	{
		m_pLibrary->ReleaseTexture(TEX_GAMEOVER);
	}

	//Csvの解放
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

/**
 * ResultSceneのコントロール
 * @return 遷移先のシーン
 */
SCENE_NUM ResultScene::Control()
{
	PadCheck();

	m_pResultBackGround->Control();
	m_pResultClock->Control();
	m_pResultText->Control();

#ifdef _DEBUG
	static int Time = 0;
	if (m_ButtonState[XINPUT_BUTTON_B] == PAD_PUSH)
	{
		Time++;
	}
	m_pResultClock->ClockControl(Time);

#endif

	//Aが押されたらLOGOに遷移する
	if (m_ButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		m_NextScene = LOGO_SCENE;
	}

	return m_NextScene;
}

/**
 * ResultSceneの描画関数
 * オブジェクトの描画を読んでるだけ
 */
void ResultScene::Draw()
{
	m_pResultBackGround->Draw();
	m_pResultText->Draw();
	m_pResultClock->Draw();
}

/**
 * ResultSceneのGamePadチェック関数
 */
void ResultScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);

#ifdef _DEBUG
	m_ButtonState[XINPUT_BUTTON_B] = m_pLibrary->GetButtonState(GAMEPAD_B, GAMEPAD1);
#endif
}
