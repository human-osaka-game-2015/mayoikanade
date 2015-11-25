#ifndef MODEMANAGER_H
#define MODEMANAGER_H


class Player;
class Brother;
class YoungerBrother;
class SceneChangeListener;
class Map;
class TimeManager;
class Shadow;

enum GAMEMODE_NUM
{
	NORMAL,
	TEXT,
	GAMEOVEREFFECT,
	GAMEOVER,
	MODEMAX
};

class ModeManager
{
private:
	Brother*				m_pBrother;
	YoungerBrother*			m_pYoungerBrother;
	SceneChangeListener*	m_pSceneChangeListener;
	Map*					m_pMap;
	TimeManager*			m_pTimeManager;
	Shadow*					m_pShadow;
	GAMEMODE_NUM			m_Mode;
	GAMEMODE_NUM CheckMode(GAMEMODE_NUM GameMode);


public:
	ModeManager(SceneChangeListener* Listener,Brother* pBrother, YoungerBrother* pYoungerBrother);
	~ModeManager();
	void Control();
	GAMEMODE_NUM GetMode();

};

#endif