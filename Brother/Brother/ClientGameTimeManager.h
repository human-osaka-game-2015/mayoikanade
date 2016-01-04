#ifndef cGAMETIMEMANAGER_H
#define cGAMETIMEMANAGER_H


class ClientModeManager;
enum GAMEMODE_NUM;


class ClientGameTimeManager
{
private:
	ClientModeManager*		m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;
	unsigned int*		m_GameTime;

public:
	ClientGameTimeManager(unsigned int* GameTime);
	~ClientGameTimeManager();
	void Control();
	void ModeManagerSet(ClientModeManager* pModeManager);
	int GetGameTime();

};


#endif