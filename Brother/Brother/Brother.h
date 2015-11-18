#ifndef _BROTHER_H_
#define _BROTHER_H_
#define BROTHERSPEAD 4
#include "Player.h"
#include "Vertex.h"

class Library;
class ModeManager;
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;
class CollisionChecker;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;


class Brother:public Player
{
private:
	int					m_Tex_Id;
	GAMEANIMA_ID		m_CurrentAnima;
	Library*			m_pLibrary;
	GAMEMODE_NUM		m_CurrentMode;
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