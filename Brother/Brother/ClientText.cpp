#include "ClientText.h"
#include "ClientModeManager.h"

ClientText::ClientText(Library* pLibrary) :m_pLibrary(pLibrary)
{
}

ClientText::~ClientText()
{

}

void ClientText::Control()
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

void ClientText::Draw()
{

}

void ClientText::ModeManagerSet(ClientModeManager* pModeManager)
{
	this->m_pModeManager = pModeManager;
}

