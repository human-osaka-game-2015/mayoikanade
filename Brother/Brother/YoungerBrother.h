#ifndef _YOUNGERBROTHER_H_
#define _YOUNGERBROTHER_H_
#include "Player.h"
#include "Vertex.h"
#include "ModeManager.h"
//ëOï˚êÈåæÇæÇØÇ≈ÇÊÇ≥Ç∞
class Library;
class CollisionChecker;



class YoungerBrother:public Player
{
private:
	Library*			m_pLibrary;
	GAMEMODE_NUM		m_CurrentScene;
	ModeManager*		m_pModeManager;
	CollisionChecker*	m_pCollisionChecker;
	LPDIRECT3DTEXTURE9	m_pTexture;

	bool*				m_pPadState;
	bool*				m_PadOldState;


public:
	YoungerBrother(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture, bool* pPadState, bool* pPadOldState);
	virtual ~YoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Init();
	void ModeManagerSet(ModeManager* Mode);

};

#endif