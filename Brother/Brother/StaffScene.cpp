#include "StaffScene.h"
#include "StaffBackGround.h"
#include "Library.h"


/**
 * StaffScene�N���X�̃R���X�g���N�^
 * @param[in] pLibrary	���C�u�����N���X
 */
StaffScene::StaffScene(Library* pLibrary) :
Scene(pLibrary)
{
	//�t�@�C���̓ǂݍ���
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("StaffTex.csv", STAFF_VERTEXINFO_MAX);
	m_pLibrary->LoadTextureEx("StaffScene.png", TEX_STAFF, 255, 0, 255, 0);

	//�I�u�W�F�N�g�̐���
	m_pStaffBackGround = new StaffBackGround(m_pLibrary);
}

/**
 * StaffScene�N���X�̃f�X�g���N�^
 */
StaffScene::~StaffScene()
{
	delete m_pStaffBackGround;
	
	m_pLibrary->ReleaseTexture(TEX_STAFF);
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->FileInfoRelease();
}

/**
 * StaffScene�N���X�̃R���X�g���N�^
 * @return �J�ڐ�̃V�[�� 
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
 * StaffScene�N���X�̕`��
 */
void StaffScene::Draw()
{
	m_pStaffBackGround->Draw();
}

/**
 * StaffScene��GamePad�̃`�F�b�N�֐�
 */
void StaffScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}

