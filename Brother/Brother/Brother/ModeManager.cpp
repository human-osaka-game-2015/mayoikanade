#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "Brother.h"
#include "YoungerBrother.h"

ModeManager::ModeManager(SceneChangeListener* Listener, Brother* pBrother, YoungerBrother* pYoungerBrother) :m_Mode(NORMAL)
{
	m_Listener = Listener;
	m_pBrother = pBrother;
	m_pYoungerBrother = pYoungerBrother;
}

ModeManager::~ModeManager()
{
	
}

void ModeManager::Control()
{
	m_Mode = CheckMode(m_Mode);

	if (m_Mode = GAMEOVER)
	{
		m_Listener->Update(GAMEOVER_UPDATE);
	}
}

GAMEMODE_NUM ModeManager::CheckMode(GAMEMODE_NUM GameMode)
{
	return NORMAL;//‰¼
}

GAMEMODE_NUM ModeManager:: GetMode()
{
	return m_Mode;
};