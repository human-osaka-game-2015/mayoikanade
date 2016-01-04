#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "ServerPlayer.h"

#define YOUNGERBROTHERHP 100
#define YOUNGERBROTHERSPEAD 7
#define YOUNGERBROTHERUIPOSX 420
#define YOUNGERBROTHERUIPOSY 100

class Library;
class ServerModeManager;
class ServerCollisionChecker;
class ServerPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum YOUNGERBROTHER_STATE
{
	YOUNGERBROTHER_STATE_NORMAL,
	YOUNGERBROTHER_STATE_MAX
};


class ServerYoungerBrother :public ServerPlayer
{
private:
	YOUNGERBROTHER_STATE m_YoungerBrotherState;

public:
	ServerYoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ServerCollisionChecker* pCollisionChecker, ServerDrawPositionSetter* pDrawPositionSetter, ServerGameTimeManager* pGameTimeManager, ServerPlayer* pPlayer);
	virtual ~ServerYoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void ModeManagerSet(ServerModeManager* pModeManager);
	void UiDraw();
	void PosChange(CustomVertex* pvertex);
	void SwitchOn();
	ServerPlayer* m_pPlayer;

};

#endif