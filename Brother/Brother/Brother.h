#ifndef _BROTHER_H_
#define _BROTHER_H_
#define BROTHERSPEAD 4
#include "Player.h"
#include "Vertex.h"
#include "ModeManager.h"
//前方宣言だけで
class Library;
class CollisionChecker;

enum BROTHER_ANIMAID
{
	WAIT_FRONT,
	WAIT_SIDE ,
	WAIT_BACK ,
	WALK_FRONT,
	WALK_SIDE ,
	WALK_BACK ,
	BROTHERMAX
};
//FRONTがこっち向き


class Brother:public Player
{
private:
	int					m_Tex_Id;
	BROTHER_ANIMAID		m_CurrentAnima;
	Library*			m_pLibrary;
	GAMEMODE_NUM		m_CurrentScene;
	ModeManager*		m_pModeManager;
	CollisionChecker*	m_pCollisionChecker;
	LPDIRECT3DTEXTURE9	m_pTexture;
	bool*				m_pPadState;
	bool*				m_pPadOldState;

public:
	Brother(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture, bool* pPadState, bool* pPadOldState,CollisionChecker* pCollisionChecker);
	virtual ~Brother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Init();
	void ModeManagerSet(ModeManager* Mode);
	Position Ppos;

};

#endif