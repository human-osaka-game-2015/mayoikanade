#ifndef _MODEMANAGER_H_
#define _MODEMANAGER_H_

class Player;
class Brother;
class YoungerBrother;
class SceneChangeListener;

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
	GAMEMODE_NUM			m_Mode;
	SceneChangeListener*	m_Listener;
	Brother*				m_pBrother;
	YoungerBrother*			m_pYoungerBrother;
	GAMEMODE_NUM CheckMode(GAMEMODE_NUM GameMode);


public:
	ModeManager(SceneChangeListener* Listener,Brother* pBrother, YoungerBrother* pYoungerBrother);
	~ModeManager();
	void Control();
	GAMEMODE_NUM GetMode();

};

#endif