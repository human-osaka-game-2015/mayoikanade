#include "ClientModeManager.h"
#include "SceneChangeListener.h"
#include "ClientBrother.h"
#include "ClientYoungerBrother.h"
#include "ClientShadow.h"
#include "ClientText.h"
#include "ClientGameTimeManager.h"

ClientModeManager::ClientModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, ClientGameTimeManager* pGameTimeManager, ClientShadow* pShadow,ClientText* pText) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pBrother(pBrother),
m_pYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow),
m_pText(pText)
{

}

ClientModeManager::~ClientModeManager()
{
	
}

void ClientModeManager::Control()
{
	m_Mode = CheckMode();

	if (m_Mode == GAMEOVER)
	{
		m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
	}
}

GAMEMODE_NUM ClientModeManager::CheckMode()
{
	
	//Brother‚ÌHp‚ª‚O‚¾‚Á‚½‚ç
	if (m_pBrother->GetHp() <= 0)
	{
		return GAMEOVER;		//‚»‚Ì‚¤‚¿GAMEOVEREFFECT‚É‚·‚é
	}

	if (m_pShadow->ShadowCheck() == true)
	{
		return GAMEOVER;
	}
	if (TEXT_TIME <= m_pTimeManager->GetGameTime() && m_pText->GetMessageEnd())
	{
		return TEXT;
	}


	return NORMAL;//‰¼
}

GAMEMODE_NUM ClientModeManager::GetMode()
{
	return m_Mode;
};