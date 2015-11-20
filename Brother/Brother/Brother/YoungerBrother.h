#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "Player.h"
#include "Vertex.h"

class Library;
class ModeManager;
class CollisionChecker;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;




class YoungerBrother:public Player
{
private:
	Library*			m_pLibrary;
	GAMEMODE_NUM		m_CurrentScene;
	ModeManager*		m_pModeManager;
	CollisionChecker*	m_pCollisionChecker;

	bool*				m_pPadState;
	bool*				m_PadOldState;


public:
	YoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState);
	virtual ~YoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Init();
	void ModeManagerSet(ModeManager* Mode);

};

#endif