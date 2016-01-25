#include "Player.h"

/**
 * Playerクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラスへのポインタ
 * @param[in] pPadState スティック状態が格納される配列
 * @param[in] pPadOldState 一つ前のスティック状態が格納される配列
 * @param[in] pButtonState ボタンの状態
 * @param[in] pCollisionChecker CollisionCheckerクラスへのポインタ
 * @param[in] pDrawPositionSetter DrawPositionSetterクラスへのポインタ
 * @param[in] pGameTimeManager GameTimeManagerクラスへのポインタ
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
 * Playerクラスのデストラクタ
 */
Player::~Player()
{

}
