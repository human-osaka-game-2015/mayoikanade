#include "GameTimeManager.h"
#include "ModeManager.h"


/**
 * GameTimeManager�̃R���X�g���N�^
 * @param[out] GameTime �Q�[���V�[�����Ԃ̃|�C���^
 */
GameTimeManager::GameTimeManager(unsigned int* GameTime) :
m_GameTime(GameTime)
{
	*m_GameTime = TIME_INIT;
}

/**
 * GameTimeManager�N���X�̃f�X�g���N�^
 */
GameTimeManager::~GameTimeManager()
{

}

/**
 * GameTimeManager�̃R���g���[���֐�
 */
void GameTimeManager::Control()
{
	(*m_GameTime)++;
}

/**
 * ModeManager���Z�b�g����֐�
 * param[in] pModeManager �Z�b�g����ModeManager�N���X�ւ̃|�C���^
 */
void GameTimeManager::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

/**
 * �Q�[�������Ԃ��擾����֐�
 * @return �Q�[�����̎���
 */
int GameTimeManager::GetGameTime()
{ 
	return *m_GameTime; 
}

