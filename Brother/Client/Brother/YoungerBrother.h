#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "Player.h"

#define YOUNGERBROTHERHP 100
#define YOUNGERBROTHERSPEAD 7
#define YOUNGERBROTHERUIPOSX 420
#define YOUNGERBROTHERUIPOSY 100

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum YOUNGERBROTHER_STATE
{
	YOUNGERBROTHER_STATE_NORMAL,
	YOUNGERBROTHER_STATE_MAX
};


class YoungerBrother:public Player
{
private:
	YOUNGERBROTHER_STATE m_YoungerBrotherState;

public:
	YoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager);
	virtual ~YoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void ModeManagerSet(ModeManager* pModeManager);
	void UiDraw();
	void SwitchOn();


};

#endif