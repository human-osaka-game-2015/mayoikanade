#include "ResultScene.h"
#include "ResultBackGround.h"
#include "ResultClock.h"
#include "ResultText.h"



/**
 * ResultScene�N���X�̃R���X�g���N�^
 * @param[in] pLibrary	���C�u�����N���X
 * @param[in] isGameClear �Q�[���N���A�������̃t���O
 */
ResultScene::ResultScene(Library* pLibrary, bool isGameClear) :
Scene(pLibrary),
m_isGameClear(isGameClear)
{

	//�t�@�C���̓ǂݍ���
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	
	//�Q�[���N���A���Q�[���I�[�o�[�ɂ���ēǂݍ��ރt�@�C����ύX
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

	//�I�u�W�F�N�g�̐���
	m_pResultBackGround = new ResultBackGround(m_pLibrary, m_isGameClear);
	m_pResultClock = new ResultClock(m_pLibrary, m_isGameClear, m_time);
	m_pResultText = new ResultText(m_pLibrary, m_isGameClear);
	
	//�J�ڐ�̃V�[����NONE�ɏ�����
	m_NextScene = SCENE_NONE;
}


/**
 * ResultScene�N���X�̃f�X�g���N�^
 */
ResultScene::~ResultScene()
{
	//�I�u�W�F�N�g�̔j��
	delete m_pResultText;
	delete m_pResultClock;
	delete m_pResultBackGround;

	//�摜�̉��
	if (m_isGameClear == true)
	{
		m_pLibrary->ReleaseTexture(TEX_GAMECLEAR);
	}
	else
	{
		m_pLibrary->ReleaseTexture(TEX_GAMEOVER);
	}

	//Csv�̉��
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

/**
 * ResultScene�̃R���g���[��
 * @return �J�ڐ�̃V�[��
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

	//A�������ꂽ��LOGO�ɑJ�ڂ���
	if (m_ButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		m_NextScene = LOGO_SCENE;
	}

	return m_NextScene;
}

/**
 * ResultScene�̕`��֐�
 * �I�u�W�F�N�g�̕`���ǂ�ł邾��
 */
void ResultScene::Draw()
{
	m_pResultBackGround->Draw();
	m_pResultText->Draw();
	m_pResultClock->Draw();
}

/**
 * ResultScene��GamePad�`�F�b�N�֐�
 */
void ResultScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);

#ifdef _DEBUG
	m_ButtonState[XINPUT_BUTTON_B] = m_pLibrary->GetButtonState(GAMEPAD_B, GAMEPAD1);
#endif
}
