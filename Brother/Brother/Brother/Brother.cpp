#include "Brother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "GameScene.h"



Brother::Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker) :
m_pLibrary(pLibrary), m_pPadState(pPadState), m_pPadOldState(pPadOldState), m_pCollisionChecker(pCollisionChecker)
{
	m_pLibrary->InitAnima(BROTHER_WAIT_FRONT);
	m_pLibrary->InitAnima(BROTHER_WAIT_SIDE);
	m_pLibrary->InitAnima(BROTHER_WAIT_BACK);
	m_pLibrary->InitAnima(BROTHER_WALK_FRONT);
	m_pLibrary->InitAnima(BROTHER_WALK_SIDE);
	m_pLibrary->InitAnima(BROTHER_WALK_BACK);

	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = BROTHER_WAIT_FRONT;

	Ppos.x = 300;
	Ppos.y = 300;
}

Brother::~Brother()
{

}

void Brother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:

		Move();
		break;
	}
}


void Brother::Draw()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:
		CustomVertex player[4];

		m_Tex_Id = m_pLibrary->AnimaControl(m_CurrentAnima);
		m_pLibrary->MakePosition(m_Tex_Id, &Ppos);
		m_pLibrary->MakeVertex(m_Tex_Id, player);
		m_pLibrary->xySet(Ppos, player);

		if (m_Direction == PLAYER_RIGHT)//�摜�̌������킩��Ȃ����牽�Ƃ������Ȃ�
		{
			m_pLibrary->UVReversal(player, LEFT_AND_RIGHT);
		}

		m_pLibrary->DrawTexture(TEX_GAME, player);
		break;
	}
}


void Brother::Move()
{

	//InitAnima�����܂��g���悤�ɂ���
	//���͂���ł��܂���������
	

	//�A�i���O�p�b�h�̓��͂��Ȃ�������
	//�ړ����Ȃ�������ҋ@�̃A�j���[�V����
	if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false && m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
	{
		switch (m_Direction)
		{
		case PLAYER_LEFT:
			m_CurrentAnima = BROTHER_WAIT_SIDE;

			break;
		case PLAYER_RIGHT:
			m_CurrentAnima = BROTHER_WAIT_SIDE;

			break;
		case PLAYER_FRONT:
			m_CurrentAnima = BROTHER_WAIT_FRONT;

			break;
		case PLAYER_BACK:
			m_CurrentAnima = BROTHER_WAIT_BACK;

			break;
		}
	}


	//���ړ��̏���
	if (m_pPadState[ANALOG_LEFT])
	{
		Ppos.x -= BROTHERSPEAD;

		if (m_pCollisionChecker->HitCheck((Ppos.x - (Ppos.w / 2)), (Ppos.y + (Ppos.h / 2))))
		{
			Ppos.x += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((Ppos.x - (Ppos.w / 2)), Ppos.y))
		{
			Ppos.x += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((Ppos.x - (Ppos.w / 2)), (Ppos.y + (Ppos.h / 2/2))))
		{
			Ppos.x += BROTHERSPEAD;
		}
		

		m_Direction = PLAYER_LEFT;
		if (m_pPadOldState[ANALOG_LEFT])
		{
			m_CurrentAnima = BROTHER_WALK_SIDE;

		}		
	}


	//�E�̈ړ�����
	if (m_pPadState[ANALOG_RIGHT])
	{
		Ppos.x += BROTHERSPEAD;
		
		if (m_pCollisionChecker->HitCheck((Ppos.x + (Ppos.w / 2)), (Ppos.y + (Ppos.h / 2))))
		{
			Ppos.x -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((Ppos.x + (Ppos.w / 2)), Ppos.y))
		{
			Ppos.x -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((Ppos.x + (Ppos.w / 2)), (Ppos.y + (Ppos.h / 2 /2))))
		{
			Ppos.x -= BROTHERSPEAD;
		}
		

		m_Direction = PLAYER_RIGHT;
		if (m_pPadOldState[ANALOG_RIGHT])
		{
			m_CurrentAnima = BROTHER_WALK_SIDE;

		}
	}


	//���ړ��̏���
	if (m_pPadState[ANALOG_DOWN])
	{	
		Ppos.y += BROTHERSPEAD;

		if (m_pCollisionChecker->HitCheck((Ppos.x + (Ppos.w / 2)), Ppos.y + (Ppos.h / 2)))
		{
			Ppos.y -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((Ppos.x - (Ppos.w / 2)), (Ppos.y + (Ppos.h / 2))))
		{
			Ppos.y -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(Ppos.x, (Ppos.y + (Ppos.h / 2))))
		{
			Ppos.y -= BROTHERSPEAD;
		}

		m_Direction = PLAYER_FRONT;
		if (m_pPadOldState[ANALOG_DOWN])
		{
			m_CurrentAnima = BROTHER_WALK_FRONT;

		}
	}


	//��ړ��̏���
	if (m_pPadState[ANALOG_UP])
	{	
		Ppos.y -= BROTHERSPEAD;
		
		if (m_pCollisionChecker->HitCheck((Ppos.x + (Ppos.w / 2)), Ppos.y - (Ppos.h / 2) + 64))
		{
			Ppos.y += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((Ppos.x - (Ppos.w / 2)), (Ppos.y - (Ppos.h / 2) + 64)))
		{
			Ppos.y += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(Ppos.x, (Ppos.y - (Ppos.h / 2) + 64)))
		{
			Ppos.y += BROTHERSPEAD;
		}

		m_Direction = PLAYER_BACK;
		if (m_pPadOldState[ANALOG_UP])
		{
			m_CurrentAnima = BROTHER_WALK_BACK;

		}
	}

}

void Brother ::ModeManagerSet(ModeManager* Mode)
{
	m_pModeManager = Mode;
}


void Brother::Init()
{
	
}