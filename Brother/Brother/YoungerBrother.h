#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "Player.h"

class Library;
class ModeManager;
class CollisionChecker;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;




class YoungerBrother:public Player
{
private:

public:
	YoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager);
	virtual ~YoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Init();
	void ModeManagerSet(ModeManager* pModeManager);

};

#endif