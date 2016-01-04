#ifndef MODEMANAGER_H
#define MODEMANAGER_H


class ServerPlayer;
class ServerBrother;
class ServerYoungerBrother;
class SceneChangeListener;
class Map;
class ServerGameTimeManager;
class ServerShadow;

enum GAMEMODE_NUM
{
	NORMAL,
	TEXT,
	GAMEOVEREFFECT,
	GAMEOVER,
	MODEMAX
};

class ServerModeManager
{
private:
	ServerBrother*				m_pBrother;
	ServerYoungerBrother*			m_pYoungerBrother;
	SceneChangeListener*	m_pSceneChangeListener;
	Map*					m_pMap;
	ServerGameTimeManager*		m_pTimeManager;
	ServerShadow*					m_pShadow;
	GAMEMODE_NUM			m_Mode;
	GAMEMODE_NUM CheckMode();


public:
	ServerModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, ServerGameTimeManager* pGameTimeManager, ServerShadow* pShadow);
	~ServerModeManager();
	void Control();
	GAMEMODE_NUM GetMode();

};

#endif