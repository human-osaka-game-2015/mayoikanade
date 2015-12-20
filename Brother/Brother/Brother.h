#ifndef BROTHER_H
#define BROTHER_H

#define BROTHERSPEAD 6				//�Z�̈ړ����x
#define BROTHERHP 100				//�Z�̍ő�HP
#define BROTHERUIPOSX 140			//�Z��UI��X���W
#define BROTHERUIPOSY 100			//�Z��UI��Y���W

#include "Player.h"

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum BROTHER_STATE
{
	BROTHER_STATE_NORMAL,
	BROTHER_STATE_WOODBOX,
	BROTHER_STATE_MAX
};


class Brother:public Player
{
private:
	BROTHER_STATE m_BrotherState;
	
public:
	Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager);
	virtual ~Brother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void UiDraw();
	void ModeManagerSet(ModeManager* pModeManager);
	void SwitchOn();
};

#endif