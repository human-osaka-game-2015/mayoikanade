#include "ClientGameTimeManager.h"
#include "ClientModeManager.h"


ClientGameTimeManager::ClientGameTimeManager(unsigned int *GameTime) :m_GameTime(GameTime)
{
	*m_GameTime = 0;
}

ClientGameTimeManager::~ClientGameTimeManager()
{

}

void ClientGameTimeManager::Control()
{
	(*m_GameTime)++;
}

void ClientGameTimeManager::ModeManagerSet(ClientModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

int ClientGameTimeManager::GetGameTime()
{
	return *m_GameTime;
}

