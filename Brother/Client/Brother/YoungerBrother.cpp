#include "YoungerBrother.h"
#include "Scene.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "GameScene.h"
#include "PlayerUI.h"

YoungerBrother::YoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager)
	:Player(pLibrary, pPadState, pPadOldState,pButtonState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager)
{
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_BACK);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_BACK);
	
	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = BROTHER_WAIT_FRONT;

	m_Ppos.x = 600;
	m_Ppos.y = 350;
	m_Hp = YOUNGERBROTHERHP;
	
	m_PlayerX -= 200;
	m_PlayerY += 50;
	m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);
	m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

	m_pPlayerUI = new PlayerUI(m_pLibrary, m_Hp, YOUNGERBROTHER_LIFEFRAME, YOUNGERBROTHER_LIFEBAR, YOUNGERBROTHERUIPOSX, YOUNGERBROTHERUIPOSY);

}

YoungerBrother::~YoungerBrother()
{
	delete m_pPlayerUI;
}



void YoungerBrother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl�֐��ł�������ق������₷���Ȃ�̂���
		Update();
		Action();
		Move();

		if (m_pButtonState[1] == PAD_PUSH)
		{
			m_Hp = 100;
		}

		break;
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		break;
	case GAMEOVER:

		break;
	}

	m_pPlayerUI->Control();
}

void YoungerBrother::Draw()
{
	CustomVertex player[4];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl�֐��ł�������ق������₷���Ȃ�̂���

		Tex_Id = m_pLibrary->AnimaControl(m_CurrentAnima);
		m_pLibrary->MakePosition(Tex_Id, &m_Ppos);
		m_pLibrary->MakeVertex(Tex_Id, player);
		m_pLibrary->xySet(m_Ppos, player);

		if (m_Direction == PLAYER_RIGHT)
		{
			m_pLibrary->UVReversal(player, LEFT_AND_RIGHT);
		}

		m_pLibrary->DrawTexture(TEX_GAME, player);

		break;
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		break;
	case GAMEOVER:

		break;
	}
}


void YoungerBrother::UiDraw()
{
	m_pPlayerUI->Draw();
}


void YoungerBrother::Move()
{


	//�ړ����Ȃ�������ҋ@�̃A�j���[�V����
	if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false &&
		m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
	{
		if (m_YoungerBrotherState == YOUNGERBROTHER_STATE_NORMAL)
		{
			switch (m_Direction)
			{
			case PLAYER_LEFT:
				m_CurrentAnima = YOUNGERBROTHER_WAIT_SIDE;

				break;
			case PLAYER_RIGHT:
				m_CurrentAnima = YOUNGERBROTHER_WAIT_SIDE;

				break;
			case PLAYER_FRONT:
				m_CurrentAnima = YOUNGERBROTHER_WAIT_FRONT;

				break;
			case PLAYER_BACK:
				m_CurrentAnima = YOUNGERBROTHER_WAIT_BACK;

				break;
			}
		}
	}




	//���ړ��̏���
	if (m_pPadState[ANALOG_LEFT])
	{
		m_PlayerX -= YOUNGERBROTHERSPEAD;

		float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;

		//�v���C���[�̍����̂����蔻��
		if (m_pCollisionChecker->HitCheck(PlayerLeft, m_Ppos.y + m_PlayerY))
		{
			m_PlayerX += YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY)))
		{
			m_PlayerX += YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY))
		{
			m_PlayerX += YOUNGERBROTHERSPEAD;
		}

		//�ʒu����������
		m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

		//�����̕ύX
		m_Direction = PLAYER_LEFT;


		if (m_pPadOldState[ANALOG_LEFT])
		{

			if (m_YoungerBrotherState == YOUNGERBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_SIDE;
			}
		}
	}




	//�E�̈ړ�����
	if (m_pPadState[ANALOG_RIGHT])
	{
		m_PlayerX += YOUNGERBROTHERSPEAD;

		float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;

		if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y + m_PlayerY))
		{
			m_PlayerX -= YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)) + m_PlayerY))
		{
			m_PlayerX -= YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY))
		{
			m_PlayerX -= YOUNGERBROTHERSPEAD;
		}


		m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

		m_Direction = PLAYER_RIGHT;

		if (m_pPadOldState[ANALOG_RIGHT])
		{
			if (m_YoungerBrotherState == YOUNGERBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_SIDE;
			}
			
		}
	}



	//���ړ��̏���
	if (m_pPadState[ANALOG_DOWN])
	{
		m_PlayerY += YOUNGERBROTHERSPEAD;

		float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;

		if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
		{
			m_PlayerY -= YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom))
		{
			m_PlayerY -= YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom))
		{
			m_PlayerY -= YOUNGERBROTHERSPEAD;
		}

		m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

		m_Direction = PLAYER_FRONT;
		if (m_pPadOldState[ANALOG_DOWN])
		{
			if (m_YoungerBrotherState == YOUNGERBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_FRONT;
			}
			
		}
	}


	//��ړ��̏���
	if (m_pPadState[ANALOG_UP])
	{
		m_PlayerY -= YOUNGERBROTHERSPEAD;

		float PlayerTop = m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY;


		if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerTop + 64))
		{
			m_PlayerY += YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64))
		{
			m_PlayerY += YOUNGERBROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64))
		{
			m_PlayerY += YOUNGERBROTHERSPEAD;
		}

		m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

		m_Direction = PLAYER_BACK;
		if (m_pPadOldState[ANALOG_UP])
		{
			if (m_YoungerBrotherState == YOUNGERBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_BACK;
			}
			
		}
	}


	float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;
	float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;
	float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;
	float PlayerTop = m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY;


	m_pCollisionChecker->SwitchOn(PlayerLeft, m_Ppos.y + m_PlayerY);
	m_pCollisionChecker->SwitchOn(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY));
	m_pCollisionChecker->SwitchOn(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY);


	m_pCollisionChecker->SwitchOn(PlayerRight, m_Ppos.y + m_PlayerY);
	m_pCollisionChecker->SwitchOn(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)) + m_PlayerY);
	m_pCollisionChecker->SwitchOn(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY);


	m_pCollisionChecker->SwitchOn(m_Ppos.x + m_PlayerX, PlayerBottom);
	m_pCollisionChecker->SwitchOn((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom);
	m_pCollisionChecker->SwitchOn((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom);


	m_pCollisionChecker->SwitchOn(m_Ppos.x + m_PlayerX, PlayerTop + 64);
	m_pCollisionChecker->SwitchOn((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64);
	m_pCollisionChecker->SwitchOn((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64);


}


void YoungerBrother::Action()
{

}


void YoungerBrother::Update()
{
	if ((m_pGameTimeManager->GetGameTime() % (60)) == 0)
	{
		m_Hp -= 3;
	}
}

void YoungerBrother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}


void YoungerBrother::Init()
{

}