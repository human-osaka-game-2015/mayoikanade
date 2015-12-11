#include "Brother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "PlayerUI.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"
#include "GameScene.h"


Brother::Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter, GameTimeManager* pGameTimeManager)
	:Player(pLibrary, pPadState, pPadOldState, pCollisionChecker, pDrawPositionSetter, pGameTimeManager)
{
	m_pLibrary->InitAnima(BROTHER_WAIT_FRONT);
	m_pLibrary->InitAnima(BROTHER_WAIT_SIDE);
	m_pLibrary->InitAnima(BROTHER_WAIT_BACK);
	m_pLibrary->InitAnima(BROTHER_WALK_FRONT);
	m_pLibrary->InitAnima(BROTHER_WALK_SIDE);
	m_pLibrary->InitAnima(BROTHER_WALK_BACK);

	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = BROTHER_WAIT_FRONT;

	m_Ppos.x = 600;
	m_Ppos.y = 350;
	m_Hp = BROTHERHP;

	//PlayerUIの生成
	m_pPlayerUI = new PlayerUI(m_pLibrary, m_Hp, BROTHER_LIFEFRAME, BROTHER_LIFEBAR, BROTHERUIPOSX, BROTHERUIPOSY);
}

Brother::~Brother()
{
	delete m_pPlayerUI;
}

void Brother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();		//現在のモードの取得

	switch (m_CurrentMode)
	{
	case NORMAL:				//NormalControl関数でも作ったほうが見やすくなるのかも
		if ((m_pGameTimeManager->GetGameTime() % (60)) == 0 )
		{
			m_Hp -= 4;
		}
		Move();

		//Debug用
		if (m_pLibrary->GetButtonState(GAMEPAD_B, GAMEPAD1) == PAD_PUSH)
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


void Brother::Draw()
{
	CustomVertex player[4];
	int Tex_Id;

	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL:											//NormalDraw関数でも作るべきかも
		
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

void Brother::UiDraw()
{
	m_pPlayerUI->Draw();
}

void Brother::Move()		//読みにくいから改善すべき
{
	//m_Pposの計算をして渡しているところとか見づらい
	//HitCheckに何を渡しているのか一見わからないから直すべき


	//移動がなかったら待機のアニメーション
	if (m_pPadState[ANALOG_LEFT] == false && m_pPadState[ANALOG_RIGHT] == false &&
		m_pPadState[ANALOG_UP] == false && m_pPadState[ANALOG_DOWN] == false)
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




	//左移動の処理
	if (m_pPadState[ANALOG_LEFT])
	{
		m_PlayerX -= BROTHERSPEAD;

		float PlayerLeft = m_Ppos.x - (m_Ppos.w / 2) + m_PlayerX;

		//プレイヤーの左側のあたり判定
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
		
		//位置情報を教える
		m_pDrawPositionSetter->DrawPositionXSet(m_PlayerX);

		//向きの変更
		m_Direction = PLAYER_LEFT;
		if (m_pPadOldState[ANALOG_LEFT])
		{
			m_CurrentAnima = BROTHER_WALK_SIDE;
		}
	}

	


	//右の移動処理
	if (m_pPadState[ANALOG_RIGHT])
	{
		m_PlayerX += BROTHERSPEAD;

		float PlayerRight = m_Ppos.x + (m_Ppos.w / 2) + m_PlayerX;

		if (m_pCollisionChecker->HitCheck(PlayerRight, m_Ppos.y))
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
			m_CurrentAnima = BROTHER_WALK_SIDE;
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
			m_CurrentAnima = BROTHER_WALK_FRONT;
		}
	}


	//上移動の処理
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
			m_CurrentAnima = BROTHER_WALK_BACK;
		}
	}
}


void Brother::Action()
{

}


void Brother::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

void Brother::Init()
{
	
}