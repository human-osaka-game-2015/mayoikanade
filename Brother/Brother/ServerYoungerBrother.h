#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "ServerPlayer.h"

#define YOUNGERBROTHER_HP 100
#define YOUNGERBROTHER_SPEAD 7
#define YOUNGERBROTHER_SLIDE_SPEADE 2
#define YOUNGERBROTHER_STANDUP_TIME 120
#define YOUNGERBROTHER_UI_POSX 420
#define YOUNGERBROTHER_UI_POSY 100

#define YOUNGERBROTHERFACEX 320
#define YOUNGERBROTHERFACEY 40


class Library;
class ServerModeManager;
class ServerCollisionChecker;
class ServerPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;


enum YOUNGERBROTHER_STATE
{
	YOUNGERBROTHER_STATE_NORMAL,
	YOUNGERBROTHER_STATE_DOWN,
	YOUNGERBROTHER_STATE_MAX
};


class ServerYoungerBrother :public ServerPlayer
{
private:
	YOUNGERBROTHER_STATE	m_YoungerBrotherState;
	int						m_StandUpTime;

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

	bool m_isnear;
	bool m_isfar;

	bool Near();
	bool Far();

};

#endif