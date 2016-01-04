#ifndef GAMETIMEMANAGER_H
#define GAMETIMEMANAGER_H


class ServerModeManager;
enum GAMEMODE_NUM;


class ServerGameTimeManager
{
private:
	ServerModeManager*		m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;
	unsigned int*		m_GameTime;

public:
	ServerGameTimeManager(unsigned int* GameTime);
	~ServerGameTimeManager();
	void Control();
	void ModeManagerSet(ServerModeManager* pModeManager);
	int GetGameTime();

};


#endif