#include "ServerYoungerBrother.h"
#include "Scene.h"
#include "ServerCollisionChecker.h"
#include "Library.h"
#include "ServerModeManager.h"
#include "ServerGameTimeManager.h"
#include "ServerDrawPositionSetter.h"
#include "ServerGameScene.h"
#include "ServerPlayerUI.h"


ServerYoungerBrother::ServerYoungerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ServerCollisionChecker* pCollisionChecker, ServerDrawPositionSetter* pDrawPositionSetter, ServerGameTimeManager* pGameTimeManager, ServerPlayer* pPlayer):
	ServerPlayer(pLibrary, pPadState, pPadOldState, pButtonState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager),
	m_pPlayer(pPlayer),
	m_StandUpTime(0)
{
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WAIT_BACK);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_SIDE);
	m_pLibrary->InitAnima(YOUNGERBROTHER_WALK_BACK);
	m_pLibrary->InitAnima(YOUNGERBROTHER_DOWN_BACK);
	m_pLibrary->InitAnima(YOUNGERBROTHER_DOWN_FRONT);
	m_pLibrary->InitAnima(YOUNGERBROTHER_DOWN_SIDE);

	
	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = BROTHER_WAIT_FRONT;

	m_Ppos.x = 720;
	m_Ppos.y = 950;
	m_Hp = YOUNGERBROTHER_HP;

	
	m_pPlayerUI = new ServerPlayerUI(m_pLibrary, m_Hp, YOUNGERBROTHER_LIFEFRAME, YOUNGERBROTHER_LIFEBAR, YOUNGERBROTHER_UI_POSX, YOUNGERBROTHER_UI_POSY);
}


ServerYoungerBrother::~ServerYoungerBrother()
{
	delete m_pPlayerUI;
}


void ServerYoungerBrother::PosChange(CustomVertex* pvertex)
{
	for (int i = 0; i < 4; i++)
	{
		pvertex[i].x -= m_pPlayer->m_PlayerX;
		pvertex[i].y -= m_pPlayer->m_PlayerY;
	}
}


void ServerYoungerBrother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl関数でも作ったほうが見やすくなるのかも
		Update();
		Action();
		Move();

		//Debug用
		//Bボタンを押したら
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


void ServerYoungerBrother::Draw()
{
	CustomVertex player[4];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl関数でも作ったほうが見やすくなるのかも

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
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		break;
	case GAMEOVER:

		break;
	}
}


void ServerYoungerBrother::UiDraw()
{
	m_pPlayerUI->Draw();
}


void ServerYoungerBrother::Move()
{
	switch (m_YoungerBrotherState)
	{
	case YOUNGERBROTHER_STATE_NORMAL:

		//移動がなかったら待機のアニメーション
		if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false &&
			m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
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


		//左移動の処理
		if (m_pPadState[ANALOG_LEFT])
		{
			m_Ppos.x -= YOUNGERBROTHER_SPEAD;

			float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2);
			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);


			//プレイヤーの左側のあたり判定
			if (m_pCollisionChecker->HitCheck(PlayerLeft, m_Ppos.y))
			{
				m_Ppos.x += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2))))
			{
				m_Ppos.x += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2))))
			{
				m_Ppos.x += YOUNGERBROTHER_SPEAD;
			}


			//向きの変更
			m_Direction = PLAYER_LEFT;

			if (m_pCollisionChecker->GrassPortRaitCheck(m_Ppos.x, PlayerBottom))
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_DOWN;
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
			m_Ppos.x += YOUNGERBROTHER_SPEAD;

			float PlayerRight = m_Ppos.x + (m_Ppos.w / 2);
			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);


			if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y))
			{
				m_Ppos.x -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2))))
			{
				m_Ppos.x -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2))))
			{
				m_Ppos.x -= YOUNGERBROTHER_SPEAD;
			}



			m_Direction = PLAYER_RIGHT;

			if (m_pCollisionChecker->GrassPortRaitCheck(m_Ppos.x, PlayerBottom))
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_DOWN;
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
			m_Ppos.y += YOUNGERBROTHER_SPEAD;

			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);

			if (m_pCollisionChecker->HitCheck(m_Ppos.x, PlayerBottom))
			{
				m_Ppos.y -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)), PlayerBottom))
			{
				m_Ppos.y -= YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)), PlayerBottom))
			{
				m_Ppos.y -= YOUNGERBROTHER_SPEAD;
			}


			m_Direction = PLAYER_FRONT;

			if (m_pCollisionChecker->GrassCheck(m_Ppos.x, PlayerBottom))
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_DOWN;
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
			m_Ppos.y -= YOUNGERBROTHER_SPEAD;

			float PlayerTop = m_Ppos.y - (m_Ppos.h / 2);
			float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);


			if (m_pCollisionChecker->HitCheck(m_Ppos.x, PlayerTop + 64))
			{
				m_Ppos.y += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)), PlayerTop + 64))
			{
				m_Ppos.y += YOUNGERBROTHER_SPEAD;
			}
			else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)), PlayerTop + 64))
			{
				m_Ppos.y += YOUNGERBROTHER_SPEAD;
			}


			m_Direction = PLAYER_BACK;

			if (m_pCollisionChecker->GrassCheck(m_Ppos.x, PlayerBottom))
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_DOWN;
				m_CurrentAnima = YOUNGERBROTHER_DOWN_BACK;
			}
			else
			{
				m_CurrentAnima = YOUNGERBROTHER_WALK_BACK;
			}


		}




		break;
	case YOUNGERBROTHER_STATE_DOWN:

		float PlayerLeft = (m_Ppos.x - YOUNGERBROTHER_SLIDE_SPEADE) - (m_Ppos.w / 2);
		float PlayerRight = (m_Ppos.x + YOUNGERBROTHER_SLIDE_SPEADE) + (m_Ppos.w / 2);
		float PlayerTop = (m_Ppos.y - YOUNGERBROTHER_SLIDE_SPEADE) - (m_Ppos.h / 2);
		float PlayerBottom = (m_Ppos.y + YOUNGERBROTHER_SLIDE_SPEADE) + (m_Ppos.h / 2);

		switch (m_Direction)
		{
		case PLAYER_LEFT:


			

			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_SIDE;
				m_Ppos.x -= 64;
				m_StandUpTime = 0;
			}

			break;
		case PLAYER_RIGHT:

			

		

			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_SIDE;
				m_Ppos.x += 64;
				m_StandUpTime = 0;
			}

			break;
		case PLAYER_BACK:



			
			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_BACK;
				m_Ppos.y -= 64;
				m_StandUpTime = 0;
			}

			break;
		case PLAYER_FRONT:



			m_StandUpTime += 2;
			if (m_StandUpTime >= YOUNGERBROTHER_STANDUP_TIME)
			{
				m_YoungerBrotherState = YOUNGERBROTHER_STATE_NORMAL;
				m_CurrentAnima = YOUNGERBROTHER_WAIT_FRONT;
				m_Ppos.y += 64;
				m_StandUpTime = 0;
			}

			break;
		}
		

		break;
	}
	



	

}


void ServerYoungerBrother::Action()
{

}


void ServerYoungerBrother::Update()
{
	if ((m_pGameTimeManager->GetGameTime() % (60)) == 0)
	{
		m_Hp -= 3;
	}
}


void ServerYoungerBrother::ModeManagerSet(ServerModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}


void ServerYoungerBrother::SwitchOn()
{



	float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2);
	float PlayerRight = m_Ppos.x + (m_Ppos.w / 2);
	float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2);
	float PlayerTop = m_Ppos.y - (m_Ppos.h / 2);


	m_pCollisionChecker->SwitchOnYoung(PlayerLeft, m_Ppos.y);
	m_pCollisionChecker->SwitchOnYoung(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2)));
	m_pCollisionChecker->SwitchOnYoung(PlayerLeft, (m_Ppos.y + (m_Ppos.h / 2 / 2)));


	m_pCollisionChecker->SwitchOnYoung(PlayerRight, m_Ppos.y);
	m_pCollisionChecker->SwitchOnYoung(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2)));
	m_pCollisionChecker->SwitchOnYoung(PlayerRight, (m_Ppos.y + (m_Ppos.h / 2 / 2)));


	m_pCollisionChecker->SwitchOnYoung(m_Ppos.x, PlayerBottom);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x + (m_Ppos.w / 2)), PlayerBottom);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x - (m_Ppos.w / 2)), PlayerBottom);


	m_pCollisionChecker->SwitchOnYoung(m_Ppos.x + m_PlayerX, PlayerTop + 64);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x + (m_Ppos.w / 2)), PlayerTop + 64);
	m_pCollisionChecker->SwitchOnYoung((m_Ppos.x - (m_Ppos.w / 2)), PlayerTop + 64);

}


void ServerYoungerBrother::Init()
{

}