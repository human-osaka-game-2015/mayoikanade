#include "ServerPlayer.h"

ServerPlayer::ServerPlayer(Library*	pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ServerCollisionChecker* pCollisionChecker, ServerDrawPositionSetter* pDrawPositionSetter, ServerGameTimeManager* pGameTimeManager)
	:m_pLibrary(pLibrary), 
	m_pPadState(pPadState), 
	m_pPadOldState(pPadOldState), 
	m_pButtonState(pButtonState),
	m_pCollisionChecker(pCollisionChecker), 
	m_pDrawPositionSetter(pDrawPositionSetter), 
	m_pGameTimeManager(pGameTimeManager)
{

}

ServerPlayer::~ServerPlayer()
{

}
