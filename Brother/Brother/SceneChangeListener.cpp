#include "SceneChangeListener.h"

/**
 * SceneChangeListener�N���X�̃R���X�g���N�^
 * @param[out] SceneNum �J�ڐ���i�[����ϐ��̃|�C���^
 * @param[out] isClear �Q�[�����N���A���������i�[����|�C���^
 */
SceneChangeListener::SceneChangeListener(SCENE_NUM* SceneNum, bool* isClear)
{
	m_pNextScene = SceneNum;
	m_pisGameClear = isClear;
}

/**
 * SceneChangeListener�N���X�̃f�X�g���N�^
 */
SceneChangeListener::~SceneChangeListener()
{

}

/**
 * �V�[�����X�V����֐�
 * @param[in] UpdateId �X�V����V�[���ւ�enum
 */
void SceneChangeListener::Update(GAMEUPDATE_NUM UpdateId)
{
	if (UpdateId == GAMEOVER_UPDATE)
	{
		*m_pisGameClear = false;
		*m_pNextScene = RESULT_SCENE;
	}
}
