#include "ClientYoungerBrother.h"
#include "Scene.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "ClientGameScene.h"
#include "PlayerUI.h"


ClientYoungerBrother::ClientYoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager):
Player(pLibrary, pPadState, pPadOldState, pButtonState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager)
{
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_BACK);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_BACK);
	m_pLibrary->InitAnima(YOUNGERBROTHER_DOWN_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_DOWN_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_DOWN_BACK);
	
	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = BROTHER_WAIT_FRONT;

	m_Ppos.x = 600;
	m_Ppos.y = 350;
	m_Hp = YOUNGERBROTHER_HP;
	m_PlayerX += -250;
	m_PlayerY += 200;

	m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);
	m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

	m_pPlayerUI = new PlayerUI(m_pLibrary, m_Hp, YOUNGERBROTHER_LIFEFRAME, YOUNGERBROTHER_LIFEBAR, SWITCH_RED_01, SWITCH_YELLOW_01, SWITCH_BLUE_01, YOUNGERBROTHER_UI_POSX, YOUNGERBROTHER_UI_POSY, YOUNGERBROTHERFACEX, YOUNGERBROTHERFACEY);

}

ClientYoungerBrother::~ClientYoungerBrother()
{
	delete m_pPlayerUI;
}



void ClientYoungerBrother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl関数でも作ったほうが見やすくなるのかも
		Update();
		Action();
		Move();

#ifdef _DEBUG
		if (m_pButtonState[1] == PAD_PUSH)
		{
			m_Hp = YOUNGERBROTHER_HP;
		}
#endif

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

void ClientYoungerBrother::Draw()
{
	CustomVertex player[4];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL://NormalControl関数でも作ったほうが見やすくなるのかも

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
	case GAMEOVER:

		break;
	}
}


void ClientYoungerBrother::UiDraw()
{
	m_pPlayerUI->Draw();
}


void ClientYoungerBrother::Move()
{

	switch (m_YoungerBrotherState)
	{
	case CLIENTYOUNGERBROTHER_STATE_NORMAL:

		//移動がなかったら待機のアニメーション
		if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false &&
			m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
		{
			if (m_YoungerBrotherState == CLIENTYOUNGERBROTHER_STATE_NORMAL)
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




		//左移動の処理
		if (m_pPadState[ANALOG_LEFT])
		{
			m_PlayerX -= YOUNGERBROTHER_SPEAD;

			float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;
			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;

			//プレイヤーの左側のあたり判定
			if (m_pCollisionChecker->HitCheck(PlayerLeft, m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY + YOUNGERBROTHERHITY))
			{
				m_PlayerX += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY)))
			{
				m_PlayerX += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2) + m_PlayerY)))
			{
				m_PlayerX += YOUNGERBROTHER_SPEAD;
			}

			//位置情報を教える
			m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

			//向きの変更
			m_Direction = PLAYER_LEFT;


			if (m_pCollisionChecker->GrassPortRaitCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
			{
				m_Hp -= 10;
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_DOWN;
				m_CurrentAnima = YOUNGERBROTHER_DOWN_SIDE;
			}
			else
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_SIDE;
			}
		}




		//右の移動処理
		if (m_pPadState[ANALOG_RIGHT])
		{
			m_PlayerX += YOUNGERBROTHER_SPEAD;

			float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;
			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;

			if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY + YOUNGERBROTHERHITY))
			{
				m_PlayerX -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)) + m_PlayerY ))
			{
				m_PlayerX -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY))
			{
				m_PlayerX -= YOUNGERBROTHER_SPEAD;
			}


			m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

			m_Direction = PLAYER_RIGHT;

			if (m_pCollisionChecker->GrassPortRaitCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
			{
				m_Hp -= 10;
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_DOWN;
				m_CurrentAnima = YOUNGERBROTHER_DOWN_SIDE;
			}
			else
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_SIDE;
			}
		}



		//下移動の処理
		if (m_pPadState[ANALOG_DOWN])
		{
			m_PlayerY += YOUNGERBROTHER_SPEAD;

			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;

			if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
			{
				m_PlayerY -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX - YOUNGERBROTHERHITX, PlayerBottom))
			{
				m_PlayerY -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX + YOUNGERBROTHERHITX, PlayerBottom))
			{
				m_PlayerY -= YOUNGERBROTHER_SPEAD;
			}

			m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

			m_Direction = PLAYER_FRONT;

			if (m_pCollisionChecker->GrassCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
			{
				m_Hp -= 10;
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_DOWN;
				m_CurrentAnima = YOUNGERBROTHER_DOWN_FRONT;
			}
			else
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_FRONT;
			}
		}


		//上移動の処理
		if (m_pPadState[ANALOG_UP])
		{
			m_PlayerY -= YOUNGERBROTHER_SPEAD;

			float PlayerTop = m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY;
			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;


			if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerTop + +YOUNGERBROTHERHITY))
			{
				m_PlayerY += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX - YOUNGERBROTHERHITX, PlayerTop + YOUNGERBROTHERHITY))
			{
				m_PlayerY += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX + YOUNGERBROTHERHITX, PlayerTop + YOUNGERBROTHERHITY))
			{
				m_PlayerY += YOUNGERBROTHER_SPEAD;
			}

			m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

			m_Direction = PLAYER_BACK;

			if (m_pCollisionChecker->GrassCheck(m_Ppos.x + m_PlayerX, PlayerBottom))
			{
				m_Hp -= 10;
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_DOWN;
				m_CurrentAnima = YOUNGERBROTHER_DOWN_BACK;
			}
			else
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_BACK;
			}
			
		}

		if (m_pCollisionChecker->AppleCheck(m_Ppos.x + m_PlayerX, m_Ppos.y + m_PlayerY))
		{
			m_Hp += 20;
		}

		break;
	case CLIENTYOUNGERBROTHER_STATE_DOWN:

		

		switch (m_Direction)
		{
		case PLAYER_LEFT:

			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_SIDE;
				m_PlayerX -= 64;
				m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

				m_StandUpTime = 0;
			}

			break;
		case PLAYER_RIGHT:

			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_SIDE;
				m_PlayerX += 64;
				m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

				m_StandUpTime = 0;
			}

			break;
		case PLAYER_BACK:

			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_BACK;
				m_PlayerY -= 64;
				m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

				m_StandUpTime = 0;
			}

			break;
		case PLAYER_FRONT:

			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = CLIENTYOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_FRONT;
				m_PlayerY += 64;
				m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

				m_StandUpTime = 0;
			}

			break;
		}

	}

	

}


void ClientYoungerBrother::Action()
{

}


void ClientYoungerBrother::SwitchOn()
{

	float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;
	float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;
	float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;
	float PlayerTop = m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY;


	m_pCollisionChecker->SwitchOnYoung(PlayerLeft, m_Ppos.y + m_PlayerY);
	m_pCollisionChecker->SwitchOnYoung(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY));
	m_pCollisionChecker->SwitchOnYoung(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY);


	m_pCollisionChecker->SwitchOnYoung(PlayerRight, m_Ppos.y + m_PlayerY);
	m_pCollisionChecker->SwitchOnYoung(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)) + m_PlayerY);
	m_pCollisionChecker->SwitchOnYoung(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)) + m_PlayerY);


	m_pCollisionChecker->SwitchOnYoung(m_Ppos.x + m_PlayerX, PlayerBottom);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerBottom);


	m_pCollisionChecker->SwitchOnYoung(m_Ppos.x + m_PlayerX, PlayerTop + 64);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + 64);

}


void ClientYoungerBrother::Update()
{
	if ((m_pGameTimeManager->GetGameTime() % (60)) == 0)
	{
		if (Far())
		{
			m_Hp -= 3;
		}
		if (Near())
		{
			m_Hp += 3;
		}
		if (m_Hp > 100)
		{
			m_Hp = 100;
		}
	}
}

void ClientYoungerBrother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

void ClientYoungerBrother::Init()
{

}


bool ClientYoungerBrother::Near()
{
	m_isnear = false;
	float Distance_x;
	float Distance_y;

	Distance_x = m_Ppos.x + m_PlayerX - m_pPlayer->GetPositionX();
	Distance_y = m_Ppos.y + m_PlayerY - m_pPlayer->GetPositionY();

	if ((pow(Distance_x, 2.0) + pow(Distance_y, 2.0))<pow(NEAR_DISTANCE, 2.0))
	{
		m_isnear = true;
	}

	return m_isnear;
}


bool ClientYoungerBrother::Far()
{
	m_isfar = false;
	float Distance_x;
	float Distance_y;

	Distance_x = m_Ppos.x + m_PlayerX - m_pPlayer->GetPositionX();
	Distance_y = m_Ppos.y + m_PlayerY - m_pPlayer->GetPositionY();

	Distance_x = static_cast<float>(pow(Distance_x, 2.0));
	Distance_y = static_cast<float>(pow(Distance_y, 2.0));

	if ((Distance_x + Distance_y) >pow(FAR_DISTANCE, 2.0))
	{
		m_isfar = true;
	}

	return m_isfar;
}


void ClientYoungerBrother::PlayerSet(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}


