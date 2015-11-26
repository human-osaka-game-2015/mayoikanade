#include "Player.h"

Player::Player(Library*	pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker) 
	:m_pLibrary(pLibrary), m_pPadState(pPadState), m_pPadOldState(pPadOldState), m_pCollisionChecker(pCollisionChecker)
{

}

Player::~Player()
{

}
