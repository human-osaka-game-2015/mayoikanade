#include "ClientPlayer.h"

ClientPlayer::ClientPlayer(Library*	pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ClientCollisionChecker* pCollisionChecker, ClientDrawPositionSetter* pDrawPositionSetter, ClientGameTimeManager* pGameTimeManager)
	:m_pLibrary(pLibrary), 
	m_pPadState(pPadState), 
	m_pPadOldState(pPadOldState), 
	m_pButtonState(pButtonState),
	m_pCollisionChecker(pCollisionChecker), 
	m_pDrawPositionSetter(pDrawPositionSetter), 
	m_pGameTimeManager(pGameTimeManager)
{

}

ClientPlayer::~ClientPlayer()
{

}
