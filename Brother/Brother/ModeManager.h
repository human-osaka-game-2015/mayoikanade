#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#define TEXT_TIME 60*6//0*35//セリフに入るまでの時間です。60*60*35は、３５分になります。

class Player;
class ServerBrother;
class ServerYoungerBrother;
class ClientBrother;
class ClientYoungerBrother;
class SceneChangeListener;
class Map;
class GameTimeManager;
class Shadow;
class Text;

enum GAMEMODE_NUM
{
	NORMAL,
	TEXT,
	STAGECHANGE,
	GAME_CLEAR,
	GAME_CLEAREFFECT,
	GAMEOVEREFFECT,
	GAMEOVER,
	MODEMAX
};

class ModeManager
{
private:
	ServerBrother*			m_pSBrother;
	ServerYoungerBrother*	m_pSYoungerBrother;
	ClientBrother*			m_pCBrother;
	ClientYoungerBrother*	m_pCYoungerBrother;	
	SceneChangeListener*	m_pSceneChangeListener;
	Map*					m_pMap;
	GameTimeManager*		m_pTimeManager;
	Shadow*					m_pShadow;
	Text*					m_pText;
	bool					m_isServer;

	GAMEMODE_NUM			m_Mode;
	GAMEMODE_NUM CheckMode();
	bool*						m_pisGameClear;


public:
	ModeManager(SceneChangeListener* Listener, ServerBrother* pBrother, ServerYoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow, Text* pText, bool* pisGameClear, Map* pMap);
	ModeManager(SceneChangeListener* Listener, ClientBrother* pBrother, ClientYoungerBrother* pYoungerBrother, GameTimeManager* pGameTimeManager, Shadow* pShadow, Text* pText, bool* pisGameClear, Map* pMap);
	~ModeManager();
	void Control();
	GAMEMODE_NUM GetMode();
	bool m_BrotherGoal;
	bool m_YoungBrotherGoal;
	int m_alpha;
	bool m_StageChange;

};

#endif