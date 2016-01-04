#ifndef ServerTEXT_H
#define ServerTEXT_H


class Library;
class ServerModeManager;
enum GAMEMODE_NUM;



class ServerText
{
private:
	Library*			m_pLibrary;
	ServerModeManager*	m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;

public:
	ServerText(Library* pLibrary);
	~ServerText();
	void Control();
	void Draw();
	void ModeManagerSet(ServerModeManager* pModeManager);

};

#endif