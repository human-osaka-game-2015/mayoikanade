#ifndef CLIENTYOUNGERBROTHER_H
#define CLIENTYOUNGERBROTHER_H

#include "Player.h"

#define YOUNGERBROTHER_HP 100
#define YOUNGERBROTHER_SPEAD 7
#define YOUNGERBROTHER_SLIDE_SPEADE 2
#define YOUNGERBROTHER_STANDUP_TIME 120
#define YOUNGERBROTHER_UI_POSX 420
#define YOUNGERBROTHER_UI_POSY 100

#define YOUNGERBROTHERFACEX 320
#define YOUNGERBROTHERFACEY 40

#define YOUNGERBROTHERHITX 10 
#define YOUNGERBROTHERHITY 80


class Library;
class ClientModeManager;
class ClientCollisionChecker;
class ClientPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;



enum CLIENTYOUNGERBROTHER_STATE
{
	CLIENTYOUNGERBROTHER_STATE_NORMAL,
	CLIENTYOUNGERBROTHER_STATE_DOWN,
	CLIENTYOUNGERBROTHER_STATE_MAX
};


class ClientYoungerBrother :public Player
{
private:
	CLIENTYOUNGERBROTHER_STATE	m_YoungerBrotherState;
	int							m_StandUpTime;

public:
	ClientYoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager);
	virtual ~ClientYoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void ModeManagerSet(ModeManager* pModeManager);
	void UiDraw();
	void SwitchOn();

	bool Near();
	bool Far();
	void PlayerSet(Player* pPlayer);

	bool m_isnear;
	bool m_isfar;
	Player* m_pPlayer;


};

#endif