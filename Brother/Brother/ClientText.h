#ifndef CLIENTTEXT_H
#define CLIENTTEXT_H


class Library;
class ClientModeManager;
enum GAMEMODE_NUM;



class ClientText
{
private:
	Library*			m_pLibrary;
	ClientModeManager*	m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;

public:
	ClientText(Library* pLibrary);
	~ClientText();
	void Control();
	void Draw();
	void ModeManagerSet(ClientModeManager* pModeManager);

};
#endif
