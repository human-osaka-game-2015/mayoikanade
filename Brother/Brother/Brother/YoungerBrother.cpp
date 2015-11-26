#include "YoungerBrother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"


YoungerBrother::YoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker) 
	:Player(pLibrary, pPadState, pPadOldState, pCollisionChecker)
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

void YoungerBrother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}


void YoungerBrother::Init()
{

}