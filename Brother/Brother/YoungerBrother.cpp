#include "YoungerBrother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"


YoungerBrother::YoungerBrother(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture, bool* pPadState, bool* pPadOldState) :m_pLibrary(pLibrary), m_pTexture(pTexture), m_pPadState(pPadState), m_PadOldState(pPadOldState)
{

}

YoungerBrother::~YoungerBrother()
{

}

void YoungerBrother::Control()
{
	m_CurrentScene = m_pModeManager->GetMode();

	switch (m_CurrentScene)
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

void YoungerBrother::ModeManagerSet(ModeManager* Mode)
{
	m_pModeManager = Mode;
}


void YoungerBrother::Init()
{

}