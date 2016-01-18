#ifndef CLIENTBROTHER_H
#define CLIENTBROTHER_H

#define BROTHER_SPEAD 6				//兄の移動速度
#define BROTHER_HP 100				//兄の最大HP
#define BROTHER_UI_POSX 140			//兄のUIのX座標
#define BROTHER_UI_POSY 100			//兄のUIのY座標

#define BROTHERFACEPOSX 40//兄の表情のx座標
#define BROTHERFACEPOSY 40//兄の表情のy座標

#define BROTHERHIT_Y 80
#define BROTHERHIT_X 5

#include "Player.h"

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum CLIENTBROTHER_STATE
{
	CLIENTBROTHER_STATE_NORMAL,
	CLIENTBROTHER_STATE_WOODBOX,
	CLIENTBROTHER_STATE_MAX
};


class ClientBrother :public Player
{
private:
	CLIENTBROTHER_STATE m_BrotherState;
	
public:
	ClientBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager, Player* pPlayer);
	virtual ~ClientBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void UiDraw();
	void ModeManagerSet(ModeManager* pModeManager);
	void PosChange(CustomVertex* pvertex);
	void SwitchOn();
	bool Near();
	bool Far();

	bool m_isnear;
	bool m_isfar;
	Player* m_pPlayer;
};

#endif