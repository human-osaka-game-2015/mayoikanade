#ifndef cSHADOW_H
#define cSHADOW_H

#include "Vertex.h"

class Library;
class ClientModeManager;
class ClientGameTimeManager;
enum GAMEMODE_NUM;


class ClientShadow
{
private:
	Library*			m_pLibrary;
	ClientModeManager*		m_pModeManager;
	ClientGameTimeManager*	m_GameTimeManager;
	GAMEMODE_NUM		m_CurrentMode;
	Position			m_Pos;

public:
	ClientShadow(Library* pLibrary, ClientGameTimeManager* pGameTimeManager);
	~ClientShadow();
	void Control();
	void Draw();
	void ModeManagerSet(ClientModeManager* pModeManager);
	bool ShadowCheck();

};



#endif