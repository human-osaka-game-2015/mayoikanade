#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

#include "ClientPlayer.h"

#define YOUNGERBROTHER_HP 100
#define YOUNGERBROTHER_SPEAD 7
#define YOUNGERBROTHER_SLIDE_SPEADE 2
#define YOUNGERBROTHER_STANDUP_TIME 120
#define YOUNGERBROTHER_UI_POSX 420
#define YOUNGERBROTHER_UI_POSY 100

#define YOUNGERBROTHERFACEX 320
#define YOUNGERBROTHERFACEY 40

#define YOUNGERBROTHERHITX 10 
#define YOUNGERBROTHERHITY 10


class Library;
class ClientModeManager;
class ClientCollisionChecker;
class ClientPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;



enum YOUNGERBROTHER_STATE
{
	YOUNGERBROTHER_STATE_NORMAL,
	YOUNGERBROTHER_STATE_DOWN,
	YOUNGERBROTHER_STATE_MAX
};


class ClientYoungerBrother :public ClientPlayer
{
private:
	YOUNGERBROTHER_STATE	m_YoungerBrotherState;
	int						m_StandUpTime;

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

	bool Near();
	bool Far();
	void PlayerSet(ClientPlayer* pPlayer);

	bool m_isnear;
	bool m_isfar;
	ClientPlayer* m_pPlayer;


};

#endif