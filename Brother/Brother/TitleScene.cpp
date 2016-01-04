#include "TitleScene.h"
#include "Library.h"
#include "TitleBackGround.h"
#include "TitleName.h"
#include "TitleTimeManager.h"
#include "TitleSelectManager.h"


TitleScene::TitleScene(Library* pLibrary) :Scene(pLibrary)
{
	//�t�@�C���̓ǂݍ���
	m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	m_pLibrary->VertexInfo_Set("TitleTex.csv", TITLE_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfo_Set("TitleAnimation.csv", TITLEANIMA_ID_MAX);
	m_pLibrary->LoadTextureEx("TitleScene.png", TEX_TITLE, 255, 0, 255, 0);
	m_pLibrary->SoundLoad("S_T_BGM.wav", TITLE_BGM);

	//�������[�v
	m_pLibrary->Sound_Operation(TITLE_BGM,SOUND_LOOP);

	//�I�u�W�F�N�g�̐���
	m_pTitleBackGround		= new TitleBackGround(m_pLibrary);
	m_pTitleName			= new TitleName(m_pLibrary);
	m_pTitleSelectManager	= new TitleSelectManager(m_pLibrary, m_PadState, m_PadOldState,m_ButtonState);
	m_pTitleTimeManager		= new TitleTimeManager(m_pLibrary, m_time);
}

TitleScene::~TitleScene()
{
	//�I�u�W�F�N�g��delete
	delete m_pTitleTimeManager;
	delete m_pTitleName;
	delete m_pTitleSelectManager;
	delete m_pTitleBackGround;

	//�ǂݍ��񂾃t�@�C���̊J��
	m_pLibrary->SoundRelease(TITLE_BGM);
	m_pLibrary->ReleaseTexture(TEX_TITLE);
	m_pLibrary->AnimaInfo_Release();
	m_pLibrary->VertexInfo_Release();
	m_pLibrary->FileInfo_Release();

}

void TitleScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_PadOldState[ANALOG_LEFT] = m_PadState[ANALOG_LEFT];
	m_PadOldState[ANALOG_RIGHT] = m_PadState[ANALOG_RIGHT];
	m_PadOldState[ANALOG_DOWN] = m_PadState[ANALOG_DOWN];
	m_PadOldState[ANALOG_UP] = m_PadState[ANALOG_UP];

	m_PadState[ANALOG_LEFT] = m_pLibrary->GetAnalogState(ANALOG_LEFT,GAMEPAD1);
	m_PadState[ANALOG_RIGHT] = m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
	m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
	m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);

	m_ButtonState[0] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);

}


SCENE_NUM TitleScene::Control()
{
	PadCheck();

	//TitleManager�̃R���g���[��
	//��莞�Ԍo�߂Ńt�F�[�h�A�E�g����������true��Ԃ��Ă���B
	if (m_pTitleTimeManager->Control())
	{
		m_NextScene = LOGO_SCENE;
	}
	else
	{
		//�Ԃ��Ă����Ԃ�l�ɂ�莟�̃V�[���𔻒f����
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

void TitleScene::Draw()
{
	m_pTitleBackGround->Draw();
	m_pTitleName->Draw();
	m_pTitleSelectManager->Draw();
	m_pTitleTimeManager->Draw();
}