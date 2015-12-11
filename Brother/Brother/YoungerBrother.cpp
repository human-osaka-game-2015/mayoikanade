#include "YoungerBrother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"

YoungerBrother::YoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager)
	:Player(pLibrary, pPadState, pPadOldState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager)
{

}

YoungerBrother::~YoungerBrother()
{

}

void YoungerBrother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:

		break;
	}
}

void YoungerBrother::Draw()
{

}

void YoungerBrother::Move()
{

}

void YoungerBrother::Action()
{

}

void YoungerBrother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}


void YoungerBrother::Init()
{

}