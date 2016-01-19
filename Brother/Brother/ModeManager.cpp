#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "ServerBrother.h"
#include "ServerYoungerBrother.h"
#include "ClientBrother.h"
#include "ClientYoungerBrother.h"
#include "Shadow.h"
#include "Text.h"
#include "GameTimeManager.h"
#include "Map.h"
#include "Tex.h"
ModeManager::ModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow, Text* pText, bool* pisGameClear, Map* pMap) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pSBrother(pBrother),
m_pSYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow),
m_pText(pText),
m_isServer(true),
m_pisGameClear(pisGameClear),
m_pMap(pMap),
m_BrotherGoal(false),
m_YoungBrotherGoal(false),
m_StageChange(false)
{

}

ModeManager::ModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow, Text* pText, bool* pisGameClear,Map* pMap) :
m_Mode(NORMAL),
m_pSceneChangeListener(Listener),
m_pCBrother(pBrother),
m_pCYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow),
m_pText(pText),
m_isServer(false),
m_pisGameClear(pisGameClear),
m_pMap(pMap),
m_BrotherGoal(false),
m_YoungBrotherGoal(false),
m_StageChange(false)
{

}

ModeManager::~ModeManager()
{
	
}

void ModeManager::Control()
{
	if (m_StageChange == true)
	{
		if (m_alpha != 254)
		{
			m_alpha++;
		}
		else
		{
			m_StageChange = false;
		}
	}

	if (m_StageChange == false)
	{
		if (m_alpha != 0)
		{
			m_alpha--;
		}
	}


	if (m_isServer == true)
	{
		m_Mode = CheckMode();
		if (m_Mode == STAGECHANGE)
		{
			if (m_pMap->m_mapstage < STAGE_MAX)
			{
				m_pSYoungerBrother->m_Ppos.x = 350.0f;
				m_pSYoungerBrother->m_Ppos.y = 550.0f;

				m_pSBrother->m_Ppos.x = 600.0f;
				m_pSBrother->m_Ppos.y = 350.0f;

				m_pSBrother->m_PlayerX = -300.0f;
				m_pSBrother->m_PlayerY = 200.0f;

				m_pMap->m_DrawPositionX = -200.0f;
				m_pMap->m_DrawPositionY = 100.0f;
				m_pMap->m_mapstage++;
				m_pMap->MapChange();
				m_YoungBrotherGoal = false;
				m_BrotherGoal = false;

			}
			else
			{
				*m_pisGameClear = true;

				m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
			}
		}

		if (m_Mode == GAMEOVER)
		{
			m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
		}
	}
	else
	{
		m_Mode = CheckMode();

		if (m_Mode == STAGECHANGE)
		{
			if (m_pMap->m_mapstage < STAGE_MAX)
			{
				m_pCBrother->m_Ppos.x = 800.0f;
				m_pCBrother->m_Ppos.y = 950.0f;

				m_pCYoungerBrother->m_PlayerX = -250.0f;
				m_pCYoungerBrother->m_PlayerY = 200.0f;

				m_pMap->m_DrawPositionX = -250.0f;
				m_pMap->m_DrawPositionY = 200.0f;
				m_pMap->m_mapstage++;
				m_pMap->MapChange();
				m_YoungBrotherGoal = false;
				m_BrotherGoal = false;
			}
			else
			{
				*m_pisGameClear = true;

				m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
			}
		}

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

		if (m_pMap->ClearCheck(m_pSBrother->m_Ppos.x + m_pSBrother->m_PlayerX, m_pSBrother->m_Ppos.y + m_pSBrother->m_PlayerY))
		{
			m_BrotherGoal = true;
			//return STAGECHANGE;
		}
		if (m_pMap->ClearCheck(m_pSYoungerBrother->m_Ppos.x, m_pSYoungerBrother->m_Ppos.y))
		{
			m_YoungBrotherGoal = true;
			//return STAGECHANGE;
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
		if (m_pMap->ClearCheck(m_pCBrother->m_Ppos.x, m_pCBrother->m_Ppos.y))
		{
			m_BrotherGoal = true;
			//return STAGECHANGE;
		}
		if (m_pMap->ClearCheck(m_pCYoungerBrother->m_Ppos.x + m_pCYoungerBrother->m_PlayerX, m_pCYoungerBrother->m_Ppos.y + m_pCYoungerBrother->m_PlayerY))
		{
			m_YoungBrotherGoal = true;
			//return STAGECHANGE;
		}

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
	
	if (m_YoungBrotherGoal == true && m_BrotherGoal == true)
	{
		m_StageChange = true;
		if (m_alpha == 254)
		{
			return STAGECHANGE;
		}
	}


	return NORMAL;
}

GAMEMODE_NUM ModeManager::GetMode()
{
	return m_Mode;
}


