#ifndef PLAYER_H
#define PLAYER_H

#include "Vertex.h"

class Library;
class ClientModeManager;
class ClientCollisionChecker;
class ClientPlayerUI;
class ClientGameTimeManager;
class ClientDrawPositionSetter;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;
enum PADSTATE;

enum PLAYER_DIRECTION
{
	PLAYER_BACK,
	PLAYER_FRONT,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_MAX
};

class ClientPlayer
{
private:

protected:
	Library*			m_pLibrary;				//���C�u�����N���X
	ClientModeManager*	m_pModeManager;			//Mode���Ǘ�����N���X�A���݂̃��[�h���擾����Ƃ��Ɏg��
	ClientCollisionChecker*	m_pCollisionChecker;	//�����蔻����Ƃ鎞�Ɏg��
	ClientDrawPositionSetter*	m_pDrawPositionSetter;	//�v���C���[���W�̐ݒ�
	ClientGameTimeManager*	m_pGameTimeManager;		//���݂̎��Ԃ��擾����
	ClientPlayerUI*		m_pPlayerUI;			//playerUI��`�悷��Ƃ��Ɏg��
	GAMEANIMA_ID		m_CurrentAnima;			//���݂̃A�j���[�V�������w��
	GAMEMODE_NUM		m_CurrentMode;			//���݂̃��[�h���w��
	bool*				m_pPadState;			//���݂̃L�[���
	bool*				m_pPadOldState;			//�ЂƂO�̃L�[���
	PADSTATE*			m_pButtonState;			//���݂̃{�^�����

	int					m_Hp;					//Player��Hp

public:
	ClientPlayer(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ClientCollisionChecker* pCollisionChecker, ClientDrawPositionSetter* pDrawPositionSetter, ClientGameTimeManager* pGameTimeManager);
	virtual ~ClientPlayer();
	virtual void Control() = 0;
	virtual void Draw()    = 0;
	virtual void Move()    = 0;
	virtual void Action()  = 0;
	virtual void Update()  = 0;
	virtual void Init()    = 0;
	inline int GetHp(){ return m_Hp; };
	PLAYER_DIRECTION m_Direction;
	Position m_Ppos;
	float m_PlayerX;
	float m_PlayerY;
};

#endif