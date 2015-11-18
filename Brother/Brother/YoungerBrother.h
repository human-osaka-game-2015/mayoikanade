#ifndef _YOUNGERBROTHER_H_
#define _YOUNGERBROTHER_H_
#include "Player.h"
#include "Vertex.h"

class Library;
class ModeManager;
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;
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