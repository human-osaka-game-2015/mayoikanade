#ifndef BROTHER_H
#define BROTHER_H

#define BROTHERSPEAD 6				//�Z�̈ړ����x
#define BROTHERHP 100				//�Z�̍ő�HP
#define BROTHER_UI_POSX 140			//�Z��UI��X���W
#define BROTHER_UI_POSY 100			//�Z��UI��Y���W

#define BROTHERFACEPOSX 40//�Z�̕\���x���W
#define BROTHERFACEPOSY 40//�Z�̕\���y���W

#define BROTHERHIT_Y 80
#define BROTHERHIT_X 5

#include "Player.h"

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum BROTHER_STATE
{
	BROTHER_STATE_NORMAL,
	BROTHER_STATE_WOODBOX,
	BROTHER_STATE_MAX
};


class ServerBrother :public Player
{
private:
	BROTHER_STATE m_BrotherState;
	
public:
	ServerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager);
	virtual ~ServerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void UiDraw();
	void ModeManagerSet(ModeManager* pModeManager);
	void SwitchOn();

	bool Near();
	bool Far();

	bool m_isnear;
	bool m_isfar;


	void PlayerSet(Player* pPlayer);
	Player* m_pPlayer;
};

#endif