#include "TitleScene.h"
#include "Library.h"
#include "TitleBackGround.h"
#include "TitleName.h"
#include "TitleTimeManager.h"
#include "TitleSelectManager.h"


/**
 * TitleSceneクラスのコンストラクタ
 * @param[in] pLibrary	ライブラリクラス
 */
TitleScene::TitleScene(Library* pLibrary) :
Scene(pLibrary),
m_isTimeOver(false)
{
	//ファイルの読み込み
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("TitleTex.csv", TITLE_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfoSet("TitleAnimation.csv", TITLEANIMA_ID_MAX);
	m_pLibrary->LoadTextureEx("TitleScene.png", TEX_TITLE, COLORMAX, COLORMIN, COLORMAX, COLORMIN);
	m_pLibrary->SoundLoad("S_T_BGM.wav", TITLE_BGM);

	//音声ループ
	m_pLibrary->SoundOperation(TITLE_BGM,SOUND_LOOP);

	//オブジェクトの生成
	m_pTitleBackGround		= new TitleBackGround(m_pLibrary);
	m_pTitleName			= new TitleName(m_pLibrary);
	m_pTitleSelectManager	= new TitleSelectManager(m_pLibrary, m_PadState, m_PadOldState,m_ButtonState);
	m_pTitleTimeManager		= new TitleTimeManager(m_pLibrary, m_time);
}

/**
 * TitleSceneクラスのコンストラクタ
 */
TitleScene::~TitleScene()
{
	//オブジェクトのdelete
	delete m_pTitleTimeManager;
	delete m_pTitleName;
	delete m_pTitleSelectManager;
	delete m_pTitleBackGround;

	//読み込んだファイルの開放
	m_pLibrary->ReleaseSound(TITLE_BGM);
	m_pLibrary->ReleaseTexture(TEX_TITLE);
	m_pLibrary->AnimaInfoRelease();
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();

}

/**
 * GamePadの状態をチェックする関数
 */
void TitleScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_PadOldState[ANALOG_LEFT]	= m_PadState[ANALOG_LEFT];
	m_PadOldState[ANALOG_RIGHT] = m_PadState[ANALOG_RIGHT];
	m_PadOldState[ANALOG_DOWN]	= m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP]	= m_PadState[ANALOG_UP];

	m_PadState[ANALOG_LEFT]		= m_pLibrary->GetAnalogState(ANALOG_LEFT,GAMEPAD1);
	m_PadState[ANALOG_RIGHT]	= m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
	m_PadState[ANALOG_DOWN]		= m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP]		= m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);

	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);

}

/**
 * TitleSceneのコントロール
 * @return 遷移先のシーン
 */
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
			m_NextScene = CONNECTING_SCENE;
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

/**
 * TitleSceneの描画
 */
void TitleScene::Draw()
{
	m_pTitleBackGround->Draw();
	m_pTitleName->Draw();
	m_pTitleSelectManager->Draw();
	m_pTitleTimeManager->Draw();
}