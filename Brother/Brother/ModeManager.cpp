#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "Brother.h"
#include "YoungerBrother.h"
#include "Shadow.h"

ModeManager::ModeManager(SceneChangeListener* Listener, Brother* pBrother, YoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pBrother(pBrother),
m_pYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow)
{

}

ModeManager::~ModeManager()
{
	
}

void ModeManager::Control()
{
	m_Mode = CheckMode();

	if (m_Mode == GAMEOVER)
	{
		m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
	}
}

GAMEMODE_NUM ModeManager::CheckMode()
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

	return NORMAL;//‰¼
}

GAMEMODE_NUM ModeManager:: GetMode()
{
	return m_Mode;
};