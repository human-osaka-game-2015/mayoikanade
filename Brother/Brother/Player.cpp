#include "Player.h"

/**
 * Player�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X�ւ̃|�C���^
 * @param[in] pPadState �X�e�B�b�N��Ԃ��i�[�����z��
 * @param[in] pPadOldState ��O�̃X�e�B�b�N��Ԃ��i�[�����z��
 * @param[in] pButtonState �{�^���̏��
 * @param[in] pCollisionChecker CollisionChecker�N���X�ւ̃|�C���^
 * @param[in] pDrawPositionSetter DrawPositionSetter�N���X�ւ̃|�C���^
 * @param[in] pGameTimeManager GameTimeManager�N���X�ւ̃|�C���^
 */
Player::Player(Library*	pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager) :
m_pLibrary(pLibrary), 
m_pPadState(pPadState), 
m_pPadOldState(pPadOldState), 
m_pButtonState(pButtonState),
m_pCollisionChecker(pCollisionChecker), 
m_pDrawPositionSetter(pDrawPositionSetter), 
m_pGameTimeManager(pGameTimeManager)
{

}

/**
 * Player�N���X�̃f�X�g���N�^
 */
Player::~Player()
{

}
