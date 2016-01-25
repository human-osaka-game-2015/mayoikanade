#include "GameTimeManager.h"
#include "ModeManager.h"


/**
 * GameTimeManagerのコンストラクタ
 * @param[out] GameTime ゲームシーン時間のポインタ
 */
GameTimeManager::GameTimeManager(unsigned int* GameTime) :
m_GameTime(GameTime)
{
	*m_GameTime = TIME_INIT;
}

/**
 * GameTimeManagerクラスのデストラクタ
 */
GameTimeManager::~GameTimeManager()
{

}

/**
 * GameTimeManagerのコントロール関数
 */
void GameTimeManager::Control()
{
	(*m_GameTime)++;
}

/**
 * ModeManagerをセットする関数
 * param[in] pModeManager セットするModeManagerクラスへのポインタ
 */
void GameTimeManager::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

/**
 * ゲーム内時間を取得する関数
 * @return ゲーム内の時間
 */
int GameTimeManager::GetGameTime()
{ 
	return *m_GameTime; 
}

