#ifndef MODEMANAGER_H
#define MODEMANAGER_H


class ClientPlayer;
class ClientBrother;
class ClientYoungerBrother;
class SceneChangeListener;
class ClientMap;
class ClientGameTimeManager;
class ClientShadow;

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
	GAMEMODE_NUM			m_Mode;
	GAMEMODE_NUM CheckMode();


public:
	ClientModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, ClientGameTimeManager* pGameTimeManager,  ClientShadow* pShadow);
	~ClientModeManager();
	void Control();
	GAMEMODE_NUM GetMode();

};

#endif