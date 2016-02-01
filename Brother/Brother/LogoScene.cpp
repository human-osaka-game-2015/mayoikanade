#include "LogoScene.h"
#include "LogoBackGround.h"
#include "Library.h"

/**
 * LogoScene�̃R���X�g���N�^
 * @param[in] pLibrary
 */
LogoScene::LogoScene(Library* pLibrary) :
Scene(pLibrary)
{
	//csv�t�@�C���̓ǂݍ���
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("LogoTex.csv", LOGO_VERTEXINFO_MAX);
	
	//�摜�̓ǂݍ���
	m_pLibrary->LoadTextureEx("LogoScene.png", TEX_LOGO, COLORMAX, COLORMIN, COLORMAX, COLORMIN);

	//���S�V�[�����I�u�W�F�N�g�̐���
	m_pLogoBackGround = new LogoBackGround(m_pLibrary);
}

/**
 * LogoScene�̃f�X�g���N�^
 */
LogoScene::~LogoScene()
{
	//�I�u�W�F�N�g�̉������
	delete m_pLogoBackGround;

	//�t�@�C���̓ǂݍ���
	m_pLibrary->ReleaseTexture(TEX_LOGO);
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

/**
 * LogoScene�̃R���g���[���֐�
 * @return �J�ڐ�̃V�[��
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
 * LogoScene�̕`��֐�
 */
void LogoScene::Draw()
{
	m_pLogoBackGround->Draw();
}

/**
 * LogoScene�ł�GamePad�`�F�b�N�֐�
 */
void LogoScene::PadCheck()
{
	//1P�̃R���g���[���[�̏�ԃ`�F�b�N
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}
