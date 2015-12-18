#include "Brother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "PlayerUI.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "GameScene.h"


Brother::Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager)
	:Player(pLibrary, pPadState, pPadOldState,pButtonState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager),
	m_BrotherState(BROTHER_STATE_NORMAL)
{
	m_pLibrary->InitAnima(BROTHER_WAIT_FRONT);
	m_pLibrary->InitAnima(BROTHER_WAIT_SIDE);
	m_pLibrary->InitAnima(BROTHER_WAIT_BACK);
	m_pLibrary->InitAnima(BROTHER_WALK_FRONT);
	m_pLibrary->InitAnima(BROTHER_WALK_SIDE);
	m_pLibrary->InitAnima(BROTHER_WALK_BACK);

	m_pLibrary->InitAnima(BROTHER_WOODBOX_WAIT_FRONT);
	m_pLibrary->InitAnima(BROTHER_WOODBOX_WAIT_SIDE);
	m_pLibrary->InitAnima(BROTHER_WOODBOX_WAIT_BACK);
	m_pLibrary->InitAnima(BROTHER_WOODBOX_WALK_FRONT);
	m_pLibrary->InitAnima(BROTHER_WOODBOX_WALK_SIDE);
	m_pLibrary->InitAnima(BROTHER_WOODBOX_WALK_BACK);

	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = BROTHER_WAIT_FRONT;

	m_Ppos.x = 600;
	m_Ppos.y = 350;
	m_Hp = BROTHERHP;
	m_PlayerX += 200;
	m_PlayerY += 600;
	m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);
	m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

	//PlayerUI�̐���
	m_pPlayerUI = new PlayerUI(m_pLibrary, m_Hp, BROTHER_LIFEFRAME, BROTHER_LIFEBAR, BROTHERUIPOSX, BROTHERUIPOSY);
}

Brother::~Brother()
{
	delete m_pPlayerUI;
}

void Brother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();		//���݂̃��[�h�̎擾

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl�֐��ł�������ق������₷���Ȃ�̂���
		switch (m_BrotherState)
		{
		case BROTHER_STATE_NORMAL:
			
			Update();
			Action();
			Move();


			//Debug�p
			//B�{�^������������
			if (m_pButtonState[1] == PAD_PUSH)
			{
				m_Hp = 100;
			}

			break;
		case BROTHER_STATE_WOODBOX:


			Update();
			Action();
			
			Move();


			//Debug�p
			if (m_pButtonState[1] == PAD_PUSH)
			{
				m_Hp = 100;
			}

			break;
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


void Brother::Draw()
{
	CustomVertex player[4];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:											//NormalDraw�֐��ł����ׂ�����
		
		switch (m_BrotherState)
		{
		case BROTHER_STATE_NORMAL:

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
		case BROTHER_STATE_WOODBOX:

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
		}

		break;
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		break;
	case GAMEOVER:

		break;
	}
}

void Brother::UiDraw()
{
	m_pPlayerUI->Draw();
}


//�_���Ȋ֐��̓T�^
//��ΏC�����ׂ������ǎ��Ԃ��Ȃ��̂ō��͂��̂܂�
void Brother::Move()
{


	//�ړ����Ȃ�������ҋ@�̃A�j���[�V����
	if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false &&
		m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
	{
		if (m_BrotherState == BROTHER_STATE_NORMAL)
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
		else if (m_BrotherState == BROTHER_STATE_WOODBOX)
		{
			switch (m_Direction)
			{
			case PLAYER_LEFT:
				m_CurrentAnima = BROTHER_WOODBOX_WAIT_SIDE;
										 
				break;					 
			case PLAYER_RIGHT:			 
				m_CurrentAnima = BROTHER_WOODBOX_WAIT_SIDE;
										 
				break;					 
			case PLAYER_FRONT:			 
				m_CurrentAnima = BROTHER_WOODBOX_WAIT_FRONT;
										 
				break;					 
			case PLAYER_BACK:			 
				m_CurrentAnima = BROTHER_WOODBOX_WAIT_BACK;

				break;
			}
		}
		
	}




	//���ړ��̏���
	if (m_pPadState[ANALOG_LEFT])
	{
		m_PlayerX -= BROTHERSPEAD;

		float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;

		//�v���C���[�̍����̂����蔻��
		if (m_pCollisionChecker->HitCheck(PlayerLeft, m_Ppos.y + m_PlayerY))
		{
			m_PlayerX += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY)))
		{
			m_PlayerX += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY))
		{
			m_PlayerX += BROTHERSPEAD;
		}
		
		//�ʒu����������
		m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

		//�����̕ύX
		m_Direction = PLAYER_LEFT;
		

		if (m_pPadOldState[ANALOG_LEFT])
		{

			if (m_BrotherState == BROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_SIDE;
			}
			else if (m_BrotherState == BROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_SIDE;
			}


		}
	}

	


	//�E�̈ړ�����
	if (m_pPadState[ANALOG_RIGHT])
	{
		m_PlayerX += BROTHERSPEAD;

		float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;

		if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y + m_PlayerY))
		{
			m_PlayerX -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)) + m_PlayerY))
		{
			m_PlayerX -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY))
		{
			m_PlayerX -= BROTHERSPEAD;
		}


		m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

		m_Direction = PLAYER_RIGHT;
		
		if (m_pPadOldState[ANALOG_RIGHT])
		{
			if (m_BrotherState == BROTHER_STATE_NORMAL)
			{					
				m_CurrentAnima = BROTHER_WALK_SIDE;
			}
			else if (m_BrotherState == BROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_SIDE;
			}
		}
	}



	//���ړ��̏���
	if (m_pPadState[ANALOG_DOWN])
	{
		m_PlayerY += BROTHERSPEAD;

		float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;

		if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
		{
			m_PlayerY -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom))
		{
			m_PlayerY -= BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom))
		{
			m_PlayerY -= BROTHERSPEAD;
		}

		m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

		m_Direction = PLAYER_FRONT;
		if (m_pPadOldState[ANALOG_DOWN])
		{
			if (m_BrotherState == BROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_FRONT;
			}
			else if (m_BrotherState == BROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_FRONT;
			}
		}
	}


	//��ړ��̏���
	if (m_pPadState[ANALOG_UP]) 
	{
		m_PlayerY -= BROTHERSPEAD;

		float PlayerTop = m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY;


		if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerTop + 64))
		{
			m_PlayerY += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64))
		{
			m_PlayerY += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64))
		{
			m_PlayerY += BROTHERSPEAD;
		}

		m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

		m_Direction = PLAYER_BACK;
		if (m_pPadOldState[ANALOG_UP])
		{
			if (m_BrotherState == BROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_BACK;
			}
			else if (m_BrotherState == BROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_BACK;
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






void Brother::Action()
{
	if (m_pButtonState[0] == PAD_PUSH)
	{
		switch (m_BrotherState)
		{
		case BROTHER_STATE_NORMAL:
			switch (m_Direction)
			{
			case PLAYER_BACK:


				if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x, m_PlayerY + m_Ppos.y - 60) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x + 30, m_PlayerY + m_Ppos.y - 60) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x - 30, m_PlayerY + m_Ppos.y - 60) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}

				break;
			case PLAYER_FRONT:

				if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x, m_PlayerY + m_Ppos.y + 111) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x+30, m_PlayerY + m_Ppos.y + 111) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x-30, m_PlayerY + m_Ppos.y + 111) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}

				break;
			case PLAYER_LEFT:

				if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x - 78, m_PlayerY + m_Ppos.y+ 10) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x - 78, m_PlayerY + m_Ppos.y + 40) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}

				break;
			case PLAYER_RIGHT:

				if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x + 78, m_PlayerY + +m_Ppos.y+10) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_PlayerX + m_Ppos.x + 78, m_PlayerY + m_Ppos.y + 40) == true)
				{
					m_BrotherState = BROTHER_STATE_WOODBOX;
				}

				break;
			}



			break;
		case BROTHER_STATE_WOODBOX:
			//������Map�ɑ΂��Ă̏���

			switch (m_BrotherState)
			{
			case BROTHER_STATE_WOODBOX:
				
				switch (m_Direction)
				{
				case PLAYER_BACK:

					if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x, m_PlayerY + m_Ppos.y - 60) == true)
					{
						m_BrotherState = BROTHER_STATE_NORMAL;
					}

					break;
				case PLAYER_FRONT:

					if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x, m_PlayerY + m_Ppos.y + 111+32) == true)
					{
						m_BrotherState = BROTHER_STATE_NORMAL;
					}

					break;
				case PLAYER_LEFT:

					if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x - 78, m_PlayerY + m_Ppos.y+64) == true)
					{
						m_BrotherState = BROTHER_STATE_NORMAL;
					}

					break;
				case PLAYER_RIGHT:

					if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x + 78, m_PlayerY + +m_Ppos.y+64) == true)
					{
						m_BrotherState = BROTHER_STATE_NORMAL;
					}

					break;
				}



			}
		}
	}
}

void Brother::Update()
{
	if ((m_pGameTimeManager->GetGameTime() % (60)) == 0)
	{
		m_Hp -= 4;
	}
}


void Brother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

void Brother::Init()
{
	
}