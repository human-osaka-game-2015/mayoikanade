#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#define TEXT_TIME 60*6//0*35//セリフに入るまでの時間です。60*60*35は、３５分になります。

class ServerPlayer;
class ServerBrother;
class ServerYoungerBrother;
class SceneChangeListener;
class Map;
class ServerGameTimeManager;
class ServerShadow;
class ServerText;

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
	ServerText*					m_pText;

	GAMEMODE_NUM			m_Mode;
	GAMEMODE_NUM CheckMode();


public:
	ServerModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, ServerGameTimeManager* pGameTimeManager, ServerShadow* pShadow, ServerText* pText);
	~ServerModeManager();
	void Control();
	GAMEMODE_NUM GetMode();

};

#endif