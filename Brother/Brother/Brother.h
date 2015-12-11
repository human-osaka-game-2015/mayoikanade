#ifndef BROTHER_H
#define BROTHER_H

#define BROTHERSPEAD 6				//�Z�̈ړ����x
#define BROTHERHP 100				//�Z�̍ő�HP
#define BROTHERUIPOSX 140			//�Z��UI��X���W
#define BROTHERUIPOSY 80			//�Z��UI��Y���W

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
	Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager);
	virtual ~Brother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Init();
	void UiDraw();
	void ModeManagerSet(ModeManager* pModeManager);

};

#endif