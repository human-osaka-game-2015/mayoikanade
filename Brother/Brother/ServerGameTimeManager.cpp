#include "ServerGameTimeManager.h"
#include "ServerModeManager.h"


ServerGameTimeManager::ServerGameTimeManager(unsigned int *GameTime) :m_GameTime(GameTime)
{
	*m_GameTime = 0;
}

ServerGameTimeManager::~ServerGameTimeManager()
{

}

void ServerGameTimeManager::Control()
{
	(*m_GameTime) ++;
}

void ServerGameTimeManager::ModeManagerSet(ServerModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

int ServerGameTimeManager::GetGameTime()
{ 
	return *m_GameTime; 
}

