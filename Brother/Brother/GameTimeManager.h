#ifndef GAMETIMEMANAGER_H
#define GAMETIMEMANAGER_H

#define TIME_INIT 0		//GameTime‚Ì‰Šú’l

class ModeManager;
enum GAMEMODE_NUM;


class GameTimeManager
{
private:
	ModeManager*		m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;
	unsigned int*		m_GameTime;

public:
	GameTimeManager(unsigned int* GameTime);
	~GameTimeManager();
	void Control();
	void ModeManagerSet(ModeManager* pModeManager);
	int GetGameTime();

};


#endif