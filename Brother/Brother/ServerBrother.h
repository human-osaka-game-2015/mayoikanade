#ifndef BROTHER_H
#define BROTHER_H

#define BROTHERSPEAD 6				//�Z�̈ړ����x
#define BROTHERHP 100				//�Z�̍ő�HP
#define BROTHERUIPOSX 140			//�Z��UI��X���W
#define BROTHERUIPOSY 100			//�Z��UI��Y���W

#include "ServerPlayer.h"

class Library;
class ServerModeManager;
class ServerCollisionChecker;
class ServerPlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum BROTHER_STATE
{
	BROTHER_STATE_NORMAL,
	BROTHER_STATE_WOODBOX,
	BROTHER_STATE_MAX
};


class ServerBrother :public ServerPlayer
{
private:
	BROTHER_STATE m_BrotherState;
	
public:
	ServerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ServerCollisionChecker* pCollisionChecker, ServerDrawPositionSetter* pDrawPositionSetter, ServerGameTimeManager* pGameTimeManager);
	virtual ~ServerBrother();
	virtual void Control();
	virtual void Draw();
	virtual void Move();
	virtual void Action();
	virtual void Update();
	virtual void Init();
	void UiDraw();
	void ModeManagerSet(ServerModeManager* pModeManager);
	void SwitchOn();
};

#endif