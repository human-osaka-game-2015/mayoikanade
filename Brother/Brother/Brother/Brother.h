#ifndef BROTHER_H
#define BROTHER_H

#define BROTHERSPEAD 4
#define BROTHERHP 100
#include "Player.h"

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

class Brother:public Player
{
private:
	
public:
	Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState,CollisionChecker* pCollisionChecker);
	virtual ~Brother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Init();
	void ModeManagerSet(ModeManager* pModeManager);

};

#endif