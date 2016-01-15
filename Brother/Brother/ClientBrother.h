#ifndef BROTHER_H
#define BROTHER_H

#define BROTHER_SPEAD 6				//兄の移動速度
#define BROTHER_HP 100				//兄の最大HP
#define BROTHER_UI_POSX 140			//兄のUIのX座標
#define BROTHER_UI_POSY 100			//兄のUIのY座標

#define BROTHERFACEPOSX 40//兄の表情のx座標
#define BROTHERFACEPOSY 40//兄の表情のy座標

#define BROTHERHIT_Y 64
#define BROTHERHIT_X 5

#include "ClientPlayer.h"

class Library;
class ModeManager;
class CollisionChecker;
class ClientPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum BROTHER_STATE
{
	BROTHER_STATE_NORMAL,
	BROTHER_STATE_WOODBOX,
	BROTHER_STATE_MAX
};


class ClientBrother :public ClientPlayer
{
private:
	BROTHER_STATE m_BrotherState;
	
public:
	ClientBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ClientCollisionChecker* pCollisionChecker, ClientDrawPositionSetter* pDrawPositionSetter, ClientGameTimeManager* pGameTimeManager, ClientPlayer* pPlayer);
	virtual ~ClientBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void UiDraw();
	void ModeManagerSet(ClientModeManager* pModeManager);
	void PosChange(CustomVertex* pvertex);
	void SwitchOn();
	bool Near();
	bool Far();

	bool m_isnear;
	bool m_isfar;
	ClientPlayer* m_pPlayer;
};

#endif