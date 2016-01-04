#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "ClientPlayer.h"

#define YOUNGERBROTHERHP 100
#define YOUNGERBROTHERSPEAD 7
#define YOUNGERBROTHERUIPOSX 420
#define YOUNGERBROTHERUIPOSY 100

class Library;
class ClientModeManager;
class ClientCollisionChecker;
class ClientPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum YOUNGERBROTHER_STATE
{
	YOUNGERBROTHER_STATE_NORMAL,
	YOUNGERBROTHER_STATE_MAX
};


class ClientYoungerBrother :public ClientPlayer
{
private:
	YOUNGERBROTHER_STATE m_YoungerBrotherState;

public:
	ClientYoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ClientCollisionChecker* pCollisionChecker, ClientDrawPositionSetter* pDrawPositionSetter, ClientGameTimeManager* pGameTimeManager);
	virtual ~ClientYoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void ModeManagerSet(ClientModeManager* pModeManager);
	void UiDraw();
	void SwitchOn();


};

#endif