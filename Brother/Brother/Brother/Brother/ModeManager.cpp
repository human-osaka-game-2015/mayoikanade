#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "Brother.h"
#include "YoungerBrother.h"

ModeManager::ModeManager(SceneChangeListener* Listener, Brother* pBrother, YoungerBrother* pYoungerBrother) :m_Mode(NORMAL)
{
	m_pSceneChangeListener = Listener;
	m_pBrother = pBrother;
	m_pYoungerBrother = pYoungerBrother;
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
		return GAMEOVER;
	}

	return NORMAL;//‰¼
}

GAMEMODE_NUM ModeManager:: GetMode()
{
	return m_Mode;
};