#include "ConnectingScene.h"
#include "ConnectSelectManager..h"
#include "IPAddSelectScene.h"
#include "ListenServer.h"
ConnectingScene::ConnectingScene(Library* pLibrary,char* IPadd) :Scene(pLibrary)
{
	m_pConnectSelectManager = new ConnectSelectManager(m_pLibrary, m_PadState, m_PadOldState);
	m_pIPAddSelectScene     = new IPAddSelectScene(m_pLibrary, IPadd);
	m_pListenServer         = new ListenServer(m_pLibrary);

	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("ConnectingTex.csv", CONNECT_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfoSet("ConnectingAnimation.csv", CONNECTANIMA_ID_MAX);
	m_pLibrary->LoadTextureEx("ConnectingScene.png", TEX_CONNECT, 255, 0, 255, 0);
	m_pLibrary->LoadTextureEx("ConnectSelect.png", CONNECTSELECT_WAIT, 255, 0, 255, 0);
	m_Client_isSelect = false;
	m_Server_isSelect = false;
	m_alpha = 255;
	m_BackGroundPos.x = CONNECTBACKGROUNDPOS_X;
	m_BackGroundPos.y = CONNECTBACKGROUNDPOS_Y;
	m_pLibrary->InitAnima(CONNECTCURSOL_ANIMA);
	m_pLibrary->SoundLoad("S_T_BGM.wav", CONNECTBGM);

	//音声ループ
	m_pLibrary->SoundOperation(CONNECTBGM, SOUND_LOOP);

	//timeの初期化
	m_time = 0;
}

ConnectingScene::~ConnectingScene()
{
	m_pLibrary->ReleaseSound(CONNECTBGM);
	m_pLibrary->ReleaseTexture(TEX_CONNECT);
	m_pLibrary->AnimaInfoRelease();
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
	delete m_pListenServer;
	delete m_pIPAddSelectScene;
	delete m_pConnectSelectManager;
}

SCENE_NUM ConnectingScene::Control()
{
	PadCheck();
	if (m_alpha != 0)
	{
		m_alpha--;
	}

	if (m_Client_isSelect)
	{
		if (m_pIPAddSelectScene->Control())
		{
			m_NextScene = CLIENT_GAME_SCENE;
		}
	}
	else
	{
		switch (m_pConnectSelectManager->Control())
		{
		case CLIENT_TYPE:
			m_NextScene = SERVER_GAME_SCENE;

			break;
		case SERVER_TYPE:
			m_Client_isSelect = true;
			m_NextScene = SCENE_NONE;

			break;
		case CONNECTSELECT_NONE:
			m_NextScene = SCENE_NONE;

			break;
		}

	}


	return m_NextScene;
}

void ConnectingScene::Draw()
{
	

	if (m_Client_isSelect)
	{
		CustomVertex background[4];
		m_pLibrary->MakeVertex(CONNECT_BACKGROUND, background);
		m_pLibrary->xySet(m_BackGroundPos, background);

		m_pLibrary->MakePosition(CONNECT_BACKGROUND, &m_BackGroundPos);
		m_pLibrary->DrawTexture(TEX_CONNECT, background);


		m_pIPAddSelectScene->Draw();
	}
	else
	{
		CustomVertex waiting[4] =
		{
			{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 0.0 },
			{ 1280.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 0.0 },
			{ 1280.0, 720.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 1.0 },
			{ 0.0, 720.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 1.0 }
		};

		m_pLibrary->DrawTexture(CONNECTSELECT_WAIT, waiting);

		m_pConnectSelectManager->Draw();
	}

	//フェードイン
	CustomVertex blackout[4];
	Position m_Pos = { 640, 512, 1280, 1024 };
	m_pLibrary->xySet(m_Pos, blackout);
	m_pLibrary->MakeVertex(CONNECT_BLACK, blackout);

	for (int i = 0; i < 4; i++)
	{
		blackout[i].color = D3DCOLOR_ARGB(m_alpha, 0, 0, 0);
	}

	m_pLibrary->DrawTexture(TEX_TITLE, blackout);

}

void ConnectingScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_PadOldState[ANALOG_DOWN] = m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP] = m_PadState[ANALOG_UP];

	m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);
	
}
