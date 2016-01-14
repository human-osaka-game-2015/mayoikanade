#ifndef PLAYER_H
#define PLAYER_H

#define NEAR_DISTANCE 200
#define FAR_DISTANCE 700

#include "Vertex.h"

class Library;
class ServerModeManager;
class ServerCollisionChecker;
class ServerPlayerUI;
class ServerGameTimeManager;
class ServerDrawPositionSetter;
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

class ServerPlayer
{
private:

protected:
	Library*					m_pLibrary;				//���C�u�����N���X
	ServerModeManager*			m_pModeManager;			//Mode���Ǘ�����N���X�A���݂̃��[�h���擾����Ƃ��Ɏg��
	ServerCollisionChecker*		m_pCollisionChecker;	//�����蔻����Ƃ鎞�Ɏg��
	ServerDrawPositionSetter*	m_pDrawPositionSetter;	//�v���C���[���W�̐ݒ�
	ServerGameTimeManager*		m_pGameTimeManager;		//���݂̎��Ԃ��擾����
	ServerPlayerUI*				m_pPlayerUI;			//playerUI��`�悷��Ƃ��Ɏg��
	GAMEANIMA_ID				m_CurrentAnima;			//���݂̃A�j���[�V�������w��
	GAMEMODE_NUM				m_CurrentMode;			//���݂̃��[�h���w��
	bool*						m_pPadState;			//���݂̃X�e�B�b�N���
	bool*						m_pPadOldState;			//�ЂƂO�̃X�e�B�b�N���
	PADSTATE*					m_pButtonState;			//���݂̃{�^�����

	int							m_Hp;					//Player��Hp

public:
	ServerPlayer(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ServerCollisionChecker* pCollisionChecker, ServerDrawPositionSetter* pDrawPositionSetter, ServerGameTimeManager* pGameTimeManager);
	virtual ~ServerPlayer();
	virtual void Control() = 0;
	virtual void Draw()    = 0;
	virtual void Move()    = 0;
	virtual void Action()  = 0;
	virtual void Update()  = 0;
	virtual void Init()    = 0;
	inline int GetHp(){ return m_Hp; };
	inline float GetPositionX(){ return m_Ppos.x; };
	inline float GetPositionY(){ return m_Ppos.y; };
	inline float GetMapPositionX(){ return m_Ppos.x + m_PlayerX; };
	inline float GetMapPositionY(){ return m_Ppos.y + m_PlayerY; };
	PLAYER_DIRECTION m_Direction;
	Position m_Ppos;
	float m_PlayerX;
	float m_PlayerY;
};

#endif