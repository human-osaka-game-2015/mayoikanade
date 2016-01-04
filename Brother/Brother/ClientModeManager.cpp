#include "ClientModeManager.h"
#include "SceneChangeListener.h"
#include "ClientBrother.h"
#include "ClientYoungerBrother.h"
#include "ClientShadow.h"

ClientModeManager::ClientModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, ClientGameTimeManager* pGameTimeManager, ClientShadow* pShadow) :
m_Mode(NORMAL), 
m_pSceneChangeListener(Listener),
m_pBrother(pBrother),
m_pYoungerBrother(pYoungerBrother),
m_pTimeManager(pGameTimeManager),
m_pShadow(pShadow)
{

}

ClientModeManager::~ClientModeManager()
{
	
}

void ClientModeManager::Control()
{
	m_Mode = CheckMode();

	if (m_Mode == GAMEOVER)
	{
		m_pSceneChangeListener->Update(GAMEOVER_UPDATE);
	}
}

GAMEMODE_NUM ClientModeManager::CheckMode()
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

GAMEMODE_NUM ClientModeManager::GetMode()
{
	return m_Mode;
};