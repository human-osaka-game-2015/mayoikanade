#ifndef SSHADOW_H
#define SSHADOW_H

#include "Vertex.h"

class Library;
class ServerModeManager;
class ServerGameTimeManager;
enum GAMEMODE_NUM;


class ServerShadow
{
private:
	Library*			m_pLibrary;
	ServerModeManager*		m_pModeManager;
	ServerGameTimeManager*	m_GameTimeManager;
	GAMEMODE_NUM		m_CurrentMode;
	Position			m_Pos;

public:
	ServerShadow(Library* pLibrary, ServerGameTimeManager* pGameTimeManager);
	~ServerShadow();
	void Control();
	void Draw();
	void ModeManagerSet(ServerModeManager* pModeManager);
	bool ShadowCheck();

};



#endif