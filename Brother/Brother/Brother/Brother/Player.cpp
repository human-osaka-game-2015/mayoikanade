#include "Player.h"

Player::Player(Library*	pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager)
	:m_pLibrary(pLibrary), m_pPadState(pPadState), m_pPadOldState(pPadOldState), m_pCollisionChecker(pCollisionChecker), m_pDrawPositionSetter(pDrawPositionSetter), m_pGameTimeManager(pGameTimeManager)
{

}

Player::~Player()
{

}
