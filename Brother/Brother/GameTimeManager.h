#ifndef GAMETIMEMANAGER_H
#define GAMETIMEMANAGER_H


class ModeManager;
enum GAMEMODE_NUM;


class GameTimeManager
{
private:
	ModeManager*		m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;
	unsigned int&				m_GameTime;

public:
	GameTimeManager(unsigned int& GameTime);
	~GameTimeManager();
	void Control();
	void ModeManagerSet(ModeManager* pModeManager);
	int GetGameTime(){return m_GameTime;};

};


#endif