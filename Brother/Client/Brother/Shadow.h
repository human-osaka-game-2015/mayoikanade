#ifndef SHADOW_H
#define SHADOW_H

#include "Vertex.h"

class Library;
class ModeManager;
class GameTimeManager;
enum GAMEMODE_NUM;


class Shadow
{
private:
	Library*			m_pLibrary;
	ModeManager*		m_pModeManager;
	GameTimeManager*	m_GameTimeManager;
	GAMEMODE_NUM		m_CurrentMode;
	Position			m_Pos;

public:
	Shadow(Library* pLibrary, GameTimeManager* pGameTimeManager);
	~Shadow();
	void Control();
	void Draw();
	void ModeManagerSet(ModeManager* pModeManager);
	bool ShadowCheck();

};



#endif