#include "Text.h"
#include "ModeManager.h"

Text::Text(Library* pLibrary) :m_pLibrary(pLibrary)
{
}

Text::~Text()
{

}

void Text::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:

		break;
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		break;
	case GAMEOVER:

		break;
	}
}

void Text::Draw()
{

}

void Text::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

