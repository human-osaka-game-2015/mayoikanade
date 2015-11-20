#ifndef BROTHER_H
#define BROTHER_H

#define BROTHERSPEAD 4
#include "Player.h"
#include "Vertex.h"

class Library;
class ModeManager;
class CollisionChecker;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

class Brother:public Player
{
private:
	enum INPUT_ID
	{
		
	};
	int					m_Tex_Id;
	GAMEANIMA_ID		m_CurrentAnima;
	GAMEMODE_NUM		m_CurrentMode;
	ModeManager*		m_pModeManager;
	CollisionChecker*	m_pCollisionChecker;
	bool*				m_pPadState;
	bool*				m_pPadOldState;

public:
	Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState,CollisionChecker* pCollisionChecker);
	virtual ~Brother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Init();
	void ModeManagerSet(ModeManager* Mode);
	Position Ppos;

};

#endif