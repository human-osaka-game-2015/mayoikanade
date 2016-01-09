#include "ServerModeManager.h"
#include "SceneChangeListener.h"
#include "ServerBrother.h"
#include "ServerYoungerBrother.h"
#include "ServerShadow.h"
#include "ServerText.h"
#include "ServerGameTimeManager.h"

ServerModeManager::ServerModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, ServerGameTimeManager* pGameTimeManager, ServerShadow* pShadow,ServerText* pText) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pBrother(pBrother),
m_pYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow),
m_pText(pText)
{

}

ServerModeManager::~ServerModeManager()
{
	
}

void ServerModeManager::Control()
{
	m_Mode = CheckMode();

	if (m_Mode == GAMEOVER)
	{
		m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
	}
}

GAMEMODE_NUM ServerModeManager::CheckMode()
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

GAMEMODE_NUM ServerModeManager::GetMode()
{
	return m_Mode;
};