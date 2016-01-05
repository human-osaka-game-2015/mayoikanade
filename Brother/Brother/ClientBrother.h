#ifndef BROTHER_H
#define BROTHER_H

#define BROTHER_SPEAD 6				//�Z�̈ړ����x
#define BROTHER_HP 100				//�Z�̍ő�HP
#define BROTHER_UI_POSX 140			//�Z��UI��X���W
#define BROTHER_UI_POSY 100			//�Z��UI��Y���W

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

	ClientPlayer* m_pPlayer;
};

#endif