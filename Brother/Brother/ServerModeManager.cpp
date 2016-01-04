#include "ServerModeManager.h"
#include "SceneChangeListener.h"
#include "ServerBrother.h"
#include "ServerYoungerBrother.h"
#include "ServerShadow.h"

ServerModeManager::ServerModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, ServerGameTimeManager* pGameTimeManager, ServerShadow* pShadow) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pBrother(pBrother),
m_pYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow)
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
	
	//Brother��Hp���O��������
	if (m_pBrother->GetHp() <= 0)
	{
		return GAMEOVER;		//���̂���GAMEOVEREFFECT�ɂ���
	}

	if (m_pShadow->ShadowCheck() == true)
	{
		return GAMEOVER;
	}

	return NORMAL;//��
}

GAMEMODE_NUM ServerModeManager::GetMode()
{
	return m_Mode;
};