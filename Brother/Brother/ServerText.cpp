#include "ServerText.h"
#include "ServerModeManager.h"

ServerText::ServerText(Library* pLibrary) :m_pLibrary(pLibrary)
{
}

ServerText::~ServerText()
{

}

void ServerText::Control()
{
	this->m_CurrentMode = this->m_pModeManager->GetMode();

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

void ServerText::Draw()
{

}

void ServerText::ModeManagerSet(ServerModeManager* pModeManager)
{
	this->m_pModeManager = pModeManager;
}

