#ifndef YOUNGERBROTHER_H
#define YOUNGERBROTHER_H

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
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;


enum YOUNGERBROTHER_STATE
{
	YOUNGERBROTHER_STATE_NORMAL,
	YOUNGERBROTHER_STATE_DOWN,
	YOUNGERBROTHER_STATE_MAX
};


class ServerYoungerBrother :public Player
{
private:
	YOUNGERBROTHER_STATE	m_YoungerBrotherState;
	int						m_StandUpTime;

public:
	ServerYoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager, Player* pPlayer);
	virtual ~ServerYoungerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void ModeManagerSet(ModeManager* pModeManager);
	void UiDraw();
	void PosChange(CustomVertex* pvertex);
	void SwitchOn();
	Player* m_pPlayer;

	bool m_isnear;
	bool m_isfar;

	bool Near();
	bool Far();

};

#endif