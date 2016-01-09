#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#define TEXT_TIME 60*6//0*35//セリフに入るまでの時間です。60*60*35は、３５分になります。

class ClientPlayer;
class ClientBrother;
class ClientYoungerBrother;
class SceneChangeListener;
class ClientMap;
class ClientGameTimeManager;
class ClientShadow;
class ClientText;

enum GAMEMODE_NUM
{
	NORMAL,
	TEXT,
	GAMEOVEREFFECT,
	GAMEOVER,
	MODEMAX
};

class ClientModeManager
{
private:
	ClientBrother*				m_pBrother;
	ClientYoungerBrother*			m_pYoungerBrother;
	SceneChangeListener*	m_pSceneChangeListener;
	ClientMap*					m_pMap;
	ClientGameTimeManager*		m_pTimeManager;
	ClientShadow*					m_pShadow;
	ClientText*					m_pText;

	GAMEMODE_NUM			m_Mode;
	GAMEMODE_NUM CheckMode();


public:
	ClientModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, ClientGameTimeManager* pGameTimeManager, ClientShadow* pShadow, ClientText* pText);
	~ClientModeManager();
	void Control();
	GAMEMODE_NUM GetMode();

};

#endif