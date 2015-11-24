#ifndef PLAYER_H
#define PLAYER_H

#include "Vertex.h"

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum PLAYER_DIRECTION
{
	PLAYER_BACK,
	PLAYER_FRONT,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_MAX
};

class Player
{
private:

protected:
	Library*			m_pLibrary;				//���C�u�����N���X
	ModeManager*		m_pModeManager;			//Mode���Ǘ�����N���X�A���݂̃��[�h���擾����Ƃ��Ɏg��
	CollisionChecker*	m_pCollisionChecker;	//�����蔻����Ƃ鎞�Ɏg��
	PlayerUI*			m_pPlayerUI;			//playerUI��`�悷��Ƃ��Ɏg��
	GAMEANIMA_ID		m_CurrentAnima;			//���݂̃A�j���[�V�������w��
	GAMEMODE_NUM		m_CurrentMode;			//���݂̃��[�h���w��
	bool*				m_pPadState;			//���݂̃L�[���
	bool*				m_pPadOldState;			//�ЂƂO�̃L�[���
	int					m_Hp;					//Player��Hp

public:
	Player(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker);
	virtual ~Player();
	virtual void Control() = 0;
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual void Init() = 0;
	PLAYER_DIRECTION m_Direction;
	Position Ppos;

};

#endif