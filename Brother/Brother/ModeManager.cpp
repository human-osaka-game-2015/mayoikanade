#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "ServerBrother.h"
#include "ServerYoungerBrother.h"
#include "ClientBrother.h"
#include "ClientYoungerBrother.h"
#include "Shadow.h"
#include "Text.h"
#include "GameTimeManager.h"


ModeManager::ModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow, Text* pText) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pSBrother(pBrother),
m_pSYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow),
m_pText(pText),
m_isServer(true)
{

}

ModeManager::ModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow, Text* pText):
m_Mode(NORMAL),
m_pSceneChangeListener(Listener),
m_pCBrother(pBrother),
m_pCYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow),
m_pText(pText),
m_isServer(false)
{

}

ModeManager::~ModeManager()
{
	
}

void ModeManager::Control()
{
	if (m_isServer == true)
	{
		m_Mode = CheckMode();

		if (m_Mode == GAMEOVER)
		{
			m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
		}
	}
	else
	{
		m_Mode = CheckMode();

		if (m_Mode == GAMEOVER)
		{
			m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
		}
	}
	
}

GAMEMODE_NUM ModeManager::CheckMode()
{
	
	if (m_isServer == true)
	{
		//Brother‚ÌHp‚ª‚O‚¾‚Á‚½‚ç
		if ((m_pSBrother->GetHp() <= 0 && m_pShadow->ShadowCheck() == false) || (m_pSYoungerBrother->GetHp() <= 0 && m_pShadow->ShadowCheck() == false))
		{
			return GAMEOVEREFFECT;		//‚»‚Ì‚¤‚¿GAMEOVEREFFECT‚É‚·‚é
		}

		if (m_pShadow->ShadowCheck() == true)
		{
			return GAMEOVER;
		}

		//if (TEXT_TIME <= m_pTimeManager->GetGameTime() && m_pText->GetMessageEnd())
		//{
		//	return TEXT;
		//}
	}
	else
	{
		//Brother‚ÌHp‚ª‚O‚¾‚Á‚½‚ç
		if ((m_pCBrother->GetHp() <= 0 && m_pShadow->ShadowCheck() == false) || (m_pCYoungerBrother->GetHp() <= 0 && m_pShadow->ShadowCheck() == false))
		{
			return GAMEOVEREFFECT;		//‚»‚Ì‚¤‚¿GAMEOVEREFFECT‚É‚·‚é
		}

		if (m_pShadow->ShadowCheck() == true)
		{
			return GAMEOVER;
		}

		//if (TEXT_TIME <= m_pTimeManager->GetGameTime() && m_pText->GetMessageEnd())
		//{
		//	return TEXT;
		//}
	}
	


	return NORMAL;
}

GAMEMODE_NUM ModeManager::GetMode()
{
	return m_Mode;
}


