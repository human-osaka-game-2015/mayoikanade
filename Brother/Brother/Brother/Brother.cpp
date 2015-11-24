#include "Brother.h"
#include "CollisionChecker.h"
#include "Library.h"
#include "ModeManager.h"
#include "PlayerUI.h"
#include "GameScene.h"


Brother::Brother(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker)
	:Player(pLibrary, pPadState, pPadOldState, pCollisionChecker)
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
	m_Hp = 100;

	//PlayerUIの生成
	m_pPlayerUI = new PlayerUI(m_pLibrary,m_Hp);
}

Brother::~Brother()
{
	delete m_pPlayerUI;
}

void Brother::Control()
{
	m_CurrentMode = m_pModeManager->GetMode();		//現在のモードの取得

	switch (m_CurrentMode)		//現在のモードから
	{
	case NORMAL:				//NormalControl関数でも作ったほうが見やすくなるのかも
		Move();

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
		m_pLibrary->MakePosition(Tex_Id, &Ppos);
		m_pLibrary->MakeVertex(Tex_Id, player);
		m_pLibrary->xySet(Ppos, player);

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

	//仕様がわからんから仮でここにおく
	m_pPlayerUI->Draw();
}


void Brother::Move()		//読みにくいから改善すべき
{
	//Pposの計算をして渡しているところとか見づらい
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


	//右の移動処理
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


	//下移動の処理
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


	//上移動の処理
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