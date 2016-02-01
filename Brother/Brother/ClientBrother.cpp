#include "ClientBrother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "PlayerUI.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "ClientGameScene.h"


ClientBrother::ClientBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager, Player* pPlayer):
Player(pLibrary, pPadState, pPadOldState, pButtonState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager),
m_BrotherState(CLIENTBROTHER_STATE_NORMAL),
m_pPlayer(pPlayer)
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

	m_Ppos.x = 300;
	m_Ppos.y = 550;
	m_Hp = BROTHER_HP;

	m_isnear = false;
	m_isfar = false;

	//PlayerUI�̐���
	m_pPlayerUI = new PlayerUI(m_pLibrary, m_Hp, BROTHER_LIFEFRAME, BROTHER_LIFEBAR, BRTOHER_FACE_01, BRTOHER_FACE_02, BRTOHER_FACE_03, BROTHER_UI_POSX, BROTHER_UI_POSY, BROTHERFACEPOSX, BROTHERFACEPOSY);
}

ClientBrother::~ClientBrother()
{
	delete m_pPlayerUI;
}


void ClientBrother::PosChange(CustomVertex* pvertex)
{
	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		pvertex[i].x -= m_pPlayer->m_PlayerX;
		pvertex[i].y -= m_pPlayer->m_PlayerY;
	}
}



void ClientBrother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();		//���݂̃��[�h�̎擾

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl�֐��ł�������ق������₷���Ȃ�̂���
		switch (m_BrotherState)
		{
		case CLIENTBROTHER_STATE_NORMAL:
			
			Update();
			Action();
			Move();


#ifdef _DEBUG
			if (m_pButtonState[XINPUT_BUTTON_B] == PAD_PUSH)
			{
				m_Hp = 100;
			}
#endif

			break;
		case CLIENTBROTHER_STATE_WOODBOX:


			Update();
			Action();
			
			Move();


#ifdef _DEBUG
			//Debug�p
			if (m_pButtonState[XINPUT_BUTTON_B] == PAD_PUSH)
			{
				m_Hp = 100;
			}
#endif

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


void ClientBrother::Draw()
{
	CustomVertex player[SQUARE_VERTEX];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:											//NormalDraw�֐��ł����ׂ�����
		
		switch (m_BrotherState)
		{
		case CLIENTBROTHER_STATE_NORMAL:

			Tex_Id = m_pLibrary->AnimaControl(m_CurrentAnima);
			m_pLibrary->MakePosition(Tex_Id, &m_Ppos);
			m_pLibrary->MakeVertex(Tex_Id, player);
			m_pLibrary->xySet(m_Ppos, player);
			PosChange(player);

			if (m_Direction == PLAYER_RIGHT)
			{
				m_pLibrary->UVReversal(player, LEFT_AND_RIGHT);
			}

			m_pLibrary->DrawTexture(TEX_GAME, player);

			break;
		case CLIENTBROTHER_STATE_WOODBOX:

			Tex_Id = m_pLibrary->AnimaControl(m_CurrentAnima);
			m_pLibrary->MakePosition(Tex_Id, &m_Ppos);
			m_pLibrary->MakeVertex(Tex_Id, player);
			m_pLibrary->xySet(m_Ppos, player);
			PosChange(player);

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
		switch (m_BrotherState)
		{
		case CLIENTBROTHER_STATE_NORMAL:

			Tex_Id = m_pLibrary->AnimaControl(m_CurrentAnima);
			m_pLibrary->MakePosition(Tex_Id, &m_Ppos);
			m_pLibrary->MakeVertex(Tex_Id, player);
			m_pLibrary->xySet(m_Ppos, player);
			PosChange(player);

			if (m_Direction == PLAYER_RIGHT)
			{
				m_pLibrary->UVReversal(player, LEFT_AND_RIGHT);
			}

			m_pLibrary->DrawTexture(TEX_GAME, player);

			break;
		case CLIENTBROTHER_STATE_WOODBOX:

			Tex_Id = m_pLibrary->AnimaControl(m_CurrentAnima);
			m_pLibrary->MakePosition(Tex_Id, &m_Ppos);
			m_pLibrary->MakeVertex(Tex_Id, player);
			m_pLibrary->xySet(m_Ppos, player);
			PosChange(player);

			if (m_Direction == PLAYER_RIGHT)
			{
				m_pLibrary->UVReversal(player, LEFT_AND_RIGHT);
			}

			m_pLibrary->DrawTexture(TEX_GAME, player);

			break;
		}
		break;
	case GAMEOVER:

		break;
	}
}

void ClientBrother::UiDraw()
{
	m_pPlayerUI->Draw();
}


//�_���Ȋ֐��̓T�^
//��ΏC�����ׂ������ǎ��Ԃ��Ȃ��̂ō��͂��̂܂�
void ClientBrother::Move()
{
	//�ړ����Ȃ�������ҋ@�̃A�j���[�V����
	if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false &&
		m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
	{
		if (m_BrotherState == CLIENTBROTHER_STATE_NORMAL)
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
		else if (m_BrotherState == CLIENTBROTHER_STATE_WOODBOX)
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
		m_Ppos.x -= BROTHER_SPEAD;

		float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2);

		//�v���C���[�̍����̂����蔻��
		if (m_pCollisionChecker->HitCheck(PlayerLeft, m_Ppos.y - (m_Ppos.h / 2) + BROTHERHIT_Y))
		{
			m_Ppos.x += BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2))))
		{
			m_Ppos.x += BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2))))
		{
			m_Ppos.x += BROTHER_SPEAD;
		}


		//�����̕ύX
		m_Direction = PLAYER_LEFT;


		if (m_pPadOldState[ANALOG_LEFT])
		{

			if (m_BrotherState == CLIENTBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_SIDE;
			}
			else if (m_BrotherState == CLIENTBROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_SIDE;
			}
		}
	}




	//�E�̈ړ�����
	if (m_pPadState[ANALOG_RIGHT])
	{
		m_Ppos.x += BROTHER_SPEAD;

		float PlayerRight = m_Ppos.x + (m_Ppos.w / 2);

		if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y - (m_Ppos.h / 2) + BROTHERHIT_Y))
		{
			m_Ppos.x -= BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2))))
		{
			m_Ppos.x -= BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2))))
		{
			m_Ppos.x -= BROTHER_SPEAD;
		}



		m_Direction = PLAYER_RIGHT;

		if (m_pPadOldState[ANALOG_RIGHT])
		{
			if (m_BrotherState == CLIENTBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_SIDE;
			}
			else if (m_BrotherState == CLIENTBROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_SIDE;
			}
		}
	}



	//���ړ��̏���
	if (m_pPadState[ANALOG_DOWN])
	{
		m_Ppos.y += BROTHER_SPEAD;

		float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);

		if (m_pCollisionChecker->HitCheck(m_Ppos.x, PlayerBottom))
		{
			m_Ppos.y -= BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)), PlayerBottom))
		{
			m_Ppos.y -= BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)), PlayerBottom))
		{
			m_Ppos.y -= BROTHER_SPEAD;
		}


		m_Direction = PLAYER_FRONT;
		if (m_pPadOldState[ANALOG_DOWN])
		{
			if (m_BrotherState == CLIENTBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_FRONT;
			}
			else if (m_BrotherState == CLIENTBROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_FRONT;
			}

		}
	}


	//��ړ��̏���
	if (m_pPadState[ANALOG_UP])
	{
		m_Ppos.y -= BROTHER_SPEAD;

		float PlayerTop = m_Ppos.y - (m_Ppos.h / 2);


		if (m_pCollisionChecker->HitCheck(m_Ppos.x, PlayerTop + BROTHERHIT_Y))
		{
			m_Ppos.y += BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)), PlayerTop + BROTHERHIT_Y))
		{
			m_Ppos.y += BROTHER_SPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)), PlayerTop + BROTHERHIT_Y))
		{
			m_Ppos.y += BROTHER_SPEAD;
		}


		m_Direction = PLAYER_BACK;
		if (m_pPadOldState[ANALOG_UP])
		{
			if (m_BrotherState == CLIENTBROTHER_STATE_NORMAL)
			{
				m_CurrentAnima = BROTHER_WALK_BACK;
			}
			else if (m_BrotherState == CLIENTBROTHER_STATE_WOODBOX)
			{
				m_CurrentAnima = BROTHER_WOODBOX_WALK_BACK;
			}
		}
	}

	if (m_pCollisionChecker->AppleCheck(m_Ppos.x, m_Ppos.y))
	{
		m_Hp += 20;
	}

}






void ClientBrother::Action()
{
	if (m_pButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		switch (m_BrotherState)
		{
		case CLIENTBROTHER_STATE_NORMAL:
			switch (m_Direction)
			{
			case PLAYER_BACK:
				if (m_pCollisionChecker->WoodBoxCheck(m_Ppos.x, m_Ppos.y - 60) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_Ppos.x + 30, m_Ppos.y - 60) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_Ppos.x - 30, m_Ppos.y - 60) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}

				break;
			case PLAYER_FRONT:

				if (m_pCollisionChecker->WoodBoxCheck( m_Ppos.x,  m_Ppos.y + 111) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_Ppos.x+30,  m_Ppos.y + 111) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck(m_Ppos.x-30,  m_Ppos.y + 111) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}

				break;
			case PLAYER_LEFT:

				if (m_pCollisionChecker->WoodBoxCheck(m_Ppos.x - 78,  m_Ppos.y+ 10) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck( m_Ppos.x - 78,  m_Ppos.y + 40) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}

				break;
			case PLAYER_RIGHT:

				if (m_pCollisionChecker->WoodBoxCheck( m_Ppos.x + 78,  +m_Ppos.y+10) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}
				else if (m_pCollisionChecker->WoodBoxCheck( m_Ppos.x + 78,  m_Ppos.y + 40) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_WOODBOX;
				}

				break;
			}

			break;
		case CLIENTBROTHER_STATE_WOODBOX:
			//������Map�ɑ΂��Ă̏���

			switch (m_Direction)
			{
			case PLAYER_BACK:

				if (m_pCollisionChecker->WoodBoxSet(m_Ppos.x, m_Ppos.y - 60) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_NORMAL;
				}

				break;
			case PLAYER_FRONT:

				if (m_pCollisionChecker->WoodBoxSet(m_Ppos.x, m_Ppos.y + 111 + 32) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_NORMAL;
				}

				break;
			case PLAYER_LEFT:

				if (m_pCollisionChecker->WoodBoxSet(m_Ppos.x - 78, m_Ppos.y + 64) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_NORMAL;
				}

				break;
			case PLAYER_RIGHT:

				if (m_pCollisionChecker->WoodBoxSet(m_Ppos.x + 78, m_Ppos.y + 64) == true)
				{
					m_BrotherState = CLIENTBROTHER_STATE_NORMAL;
				}

				break;
			}
		}
	}
}


void ClientBrother::Update()
{
	if ((m_pGameTimeManager->GetGameTime() % (60)) == 0)
	{
		if (Far())
		{
			m_Hp -= 4;
		}
		if (Near())
		{
			m_Hp += 4;
		}
		if (m_Hp > 100)
		{
			m_Hp = 100;
		}
	}
}


bool ClientBrother::Near()
{
	m_isnear = false;
	float Distance_x;
	float Distance_y;

	Distance_x = m_Ppos.x - m_pPlayer->GetMapPositionX();
	Distance_y = m_Ppos.y - m_pPlayer->GetMapPositionY();

	Distance_x = static_cast<float>(pow(Distance_x, 2.0));
	Distance_y = static_cast<float>(pow(Distance_y, 2.0));

	if ((Distance_x + Distance_y)<pow(NEAR_DISTANCE, 2.0))
	{
		m_isnear = true;
	}
	return m_isnear;
}


bool ClientBrother::Far()
{
	m_isfar = false;
	float Distance_x;
	float Distance_y;

	Distance_x = m_Ppos.x - m_pPlayer->GetMapPositionX();
	Distance_y = m_Ppos.y - m_pPlayer->GetMapPositionY();

	Distance_x = static_cast<float>(pow(Distance_x, 2.0));
	Distance_y = static_cast<float>(pow(Distance_y, 2.0));

	if ((Distance_x + Distance_y)>pow(FAR_DISTANCE, 2.0))
	{
		m_isfar = true;
	}

	return m_isfar;
}


void ClientBrother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

void ClientBrother::SwitchOn()
{
	float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2);
	float PlayerRight = m_Ppos.x + (m_Ppos.w / 2);
	float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);
	float PlayerTop = m_Ppos.y - (m_Ppos.h / 2);

	m_pCollisionChecker->SwitchOn(PlayerLeft, m_Ppos.y);
	m_pCollisionChecker->SwitchOn(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2)));
	m_pCollisionChecker->SwitchOn(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2)));

	m_pCollisionChecker->SwitchOn(PlayerRight, m_Ppos.y);
	m_pCollisionChecker->SwitchOn(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)));
	m_pCollisionChecker->SwitchOn(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)));

	m_pCollisionChecker->SwitchOn(m_Ppos.x, PlayerBottom);
	m_pCollisionChecker->SwitchOn((m_Ppos.x + (m_Ppos.w / 2)), PlayerBottom);
	m_pCollisionChecker->SwitchOn((m_Ppos.x - (m_Ppos.w / 2)), PlayerBottom);

	m_pCollisionChecker->SwitchOn(m_Ppos.x + m_PlayerX, PlayerTop + 64);
	m_pCollisionChecker->SwitchOn((m_Ppos.x + (m_Ppos.w / 2)), PlayerTop + 64);
	m_pCollisionChecker->SwitchOn((m_Ppos.x - (m_Ppos.w / 2)), PlayerTop + 64);

}


void ClientBrother::Init()
{
	
}