#ifndef CLIENTYOUNGERBROTHER_H
#define CLIENTYOUNGERBROTHER_H

#include "Player.h"

#define YOUNGERBROTHER_HP 100				//��̗̑͂̍ő�l
#define YOUNGERBROTHER_SPEAD 7				//��̃X�s�[�h
#define YOUNGERBROTHER_STANDUP_TIME 120		//�킪�����オ�鎞��
#define YOUNGERBROTHER_UI_POSX 420			//���UI��X���W
#define YOUNGERBROTHER_UI_POSY 100			//���UI��Y���W
#define YOUNGERBROTHERFACEX 320				//��̕\��\�������X���W
#define YOUNGERBROTHERFACEY 40				//��̕\��\�������Y���W
#define YOUNGERBROTHERHITX 10 				//��̂����蔻����Ƃ�ۂ�X�̕␳�l
#define YOUNGERBROTHERHITY 80				//��̂����蔻����Ƃ�ۂ�Y�̕␳�l


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