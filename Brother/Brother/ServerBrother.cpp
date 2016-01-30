#include "ServerBrother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "PlayerUI.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "ServerGameScene.h"


ServerBrother::ServerBrother(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager):
Player(pLibrary, pPadState, pPadOldState, pButtonState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager),
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
	m_PlayerX += -300;
	m_PlayerY += 200;
	m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);
	m_pDrawPositionSetter->DrawPositionYSet(m_PlayerY);

	//PlayerUIの生成
	m_pPlayerUI = new PlayerUI(m_pLibrary, m_Hp, BROTHER_LIFEFRAME, BROTHER_LIFEBAR, BRTOHER_FACE_01, BRTOHER_FACE_02, BRTOHER_FACE_03, BROTHER_UI_POSX, BROTHER_UI_POSY, BROTHERFACEPOSX, BROTHERFACEPOSY);
}

ServerBrother::~ServerBrother()
{
	delete m_pPlayerUI;
}

void ServerBrother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();		//現在のモードの取得

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl関数でも作ったほうが見やすくなるのかも
		switch (m_BrotherState)
		{
		case BROTHER_STATE_NORMAL:
			
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
		case BROTHER_STATE_WOODBOX:


			Update();
			Action();
			
			Move();


			//Debug用
			if (m_pButtonState[XINPUT_BUTTON_B] == PAD_PUSH)
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


void ServerBrother::Draw()
{
	CustomVertex player[4];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:											//NormalDraw関数でも作るべきかも
		
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
		}
		break;
	case GAMEOVER:

		break;
	}
}

void ServerBrother::UiDraw()
{
	m_pPlayerUI->Draw();
}


//ダメな関数の典型
//絶対修正すべきだけど時間がないので今はこのまま
void ServerBrother::Move()
{


	//移動がなかったら待機のアニメーション
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




	//左移動の処理
	if (m_pPadState[ANALOG_LEFT])
	{
		m_PlayerX -= BROTHERSPEAD;

		float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;

		//プレイヤーの左側のあたり判定
		if (m_pCollisionChecker->HitCheck(PlayerLeft, m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY + BROTHERHIT_Y))
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
		
		//位置情報を教える
		m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

		//向きの変更
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

	


	//右の移動処理
	if (m_pPadState[ANALOG_RIGHT])
	{
		m_PlayerX += BROTHERSPEAD;

		float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;

		if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY + BROTHERHIT_Y))
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



	//下移動の処理
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


	//上移動の処理
	if (m_pPadState[ANALOG_UP]) 
	{
		m_PlayerY -= BROTHERSPEAD;

		float PlayerTop = m_Ppos.y - (m_Ppos.h / 2) + m_PlayerY;


		if (m_pCollisionChecker->HitCheck(m_Ppos.x + m_PlayerX, PlayerTop + BROTHERHIT_Y))
		{
			m_PlayerY += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x + (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + BROTHERHIT_Y))
		{
			m_PlayerY += BROTHERSPEAD;
		}
		else if (m_pCollisionChecker->HitCheck((m_Ppos.x - (m_Ppos.w / 2)) + m_PlayerX, PlayerTop + BROTHERHIT_Y))
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

	if (m_pCollisionChecker->AppleCheck(m_Ppos.x + m_PlayerX, m_Ppos.y + m_PlayerY))
	{
		m_Hp += 20;
	}
}




void ServerBrother::Action()
{
	if (m_pButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
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
			//ここでMapに対しての処理

			switch (m_Direction)
			{
			case PLAYER_BACK:

				if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x, m_PlayerY + m_Ppos.y - 60) == true)
				{
					m_BrotherState = BROTHER_STATE_NORMAL;
				}

				break;
			case PLAYER_FRONT:

				if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x, m_PlayerY + m_Ppos.y + 111 + 32) == true)
				{
					m_BrotherState = BROTHER_STATE_NORMAL;
				}

				break;
			case PLAYER_LEFT:

				if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x - 78, m_PlayerY + m_Ppos.y + 64) == true)
				{
					m_BrotherState = BROTHER_STATE_NORMAL;
				}

				break;
			case PLAYER_RIGHT:

				if (m_pCollisionChecker->WoodBoxSet(m_PlayerX + m_Ppos.x + 78, m_PlayerY +m_Ppos.y + 64) == true)
				{
					m_BrotherState = BROTHER_STATE_NORMAL;
				}

				break;
			}
		}
	}
}

void ServerBrother::Update()
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


void ServerBrother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

void ServerBrother::SwitchOn()
{
	float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2)  + m_PlayerX;
	float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;
	float PlayerBottom = m_Ppos.y + (m_Ppos.h / 2) + m_PlayerY;
	float PlayerTop = m_Ppos.y - (m_Ppos.h / 2)   + m_PlayerY;


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

void ServerBrother::Init()
{
	
}




bool ServerBrother::Near()
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


bool ServerBrother::Far()
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

void ServerBrother::PlayerSet(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}
