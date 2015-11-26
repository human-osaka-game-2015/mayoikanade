#include "GameTimeManager.h"
#include "ModeManager.h"


GameTimeManager::GameTimeManager(unsigned int& GameTime) :m_GameTime(GameTime)
{
	m_GameTime = 0;
}

GameTimeManager::~GameTimeManager()
{

}

void GameTimeManager::Control()
{
	m_GameTime++;
}

void GameTimeManager::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}


inline int GameTimeManager::GetGameTime()
{ 
	return m_GameTime; 
}
