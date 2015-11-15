#include "Brother.h"
#include "CollisionChecker.h"
#include "Library.h"


Brother::Brother(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker) :
m_pLibrary(pLibrary), m_pTexture(pTexture), m_pPadState(pPadState), m_pPadOldState(pPadOldState), m_pCollisionChecker(pCollisionChecker)
{
	m_pLibrary->m_pUVSetter->InitAnima(WAIT_FRONT);
	m_pLibrary->m_pUVSetter->InitAnima(WAIT_SIDE);
	m_pLibrary->m_pUVSetter->InitAnima(WAIT_BACK);
	m_pLibrary->m_pUVSetter->InitAnima(WALK_FRONT);
	m_pLibrary->m_pUVSetter->InitAnima(WALK_SIDE);
	m_pLibrary->m_pUVSetter->InitAnima(WALK_BACK);

	m_Direction = PLAYER_FRONT;
	m_CurrentAnima = WAIT_FRONT;

	Ppos.x = 300;
	Ppos.y = 300;
}

Brother::~Brother()
{
	m_pLibrary->m_pUVSetter->FileInfo_Release();
	m_pLibrary->m_pUVSetter->VertexInfo_Release();
	m_pLibrary->m_pUVSetter->AnimaInfo_Release();
}

void Brother::Control()
{
	m_CurrentScene = m_pModeManager->GetMode();

	switch (m_CurrentScene)
	{
	case NORMAL:

		Move();
		break;
	}
}


void Brother::Draw()
{
	m_CurrentScene = m_pModeManager->GetMode();

	switch (m_CurrentScene)
	{
	case NORMAL:
		CustomVertex player[4];

		m_Tex_Id = m_pLibrary->m_pUVSetter->AnimaControl(m_CurrentAnima);
		m_pLibrary->m_pUVSetter->MakePosition(m_Tex_Id, &Ppos);
		m_pLibrary->m_pUVSetter->MakeVertex(m_Tex_Id, player);
		m_pLibrary->m_pVertex->xySet(Ppos, player);

		if (m_Direction == PLAYER_RIGHT)//画像の向きがわからないから何とも言えない
		{
			m_pLibrary->m_pUVSetter->UVReversal(player, LEFT_AND_RIGHT);
		}

		m_pLibrary->m_pVertex->Set_Draw_Tex(m_pTexture,player);
		break;
	}
}


void Brother::Move()
{

	//InitAnimaをうまく使うようにする
	//αはこれでもまあいいかな
	

	//アナログパッドの入力がなかったら
	//移動がなかったら待機のアニメーション
	if (m_pPadState[PAD_LEFT] == false && m_pPadState[PAD_RIGHT] == false && m_pPadState[PAD_UP] == false && m_pPadState[PAD_DOWN] == false)
	{
		switch (m_Direction)
		{
		case PLAYER_LEFT:
			m_CurrentAnima = WAIT_SIDE;

			break;
		case PLAYER_RIGHT:
			m_CurrentAnima = WAIT_SIDE;

			break;
		case PLAYER_FRONT:
			m_CurrentAnima = WAIT_FRONT;

			break;
		case PLAYER_BACK:
			m_CurrentAnima = WAIT_BACK;

			break;
		}
	}


	//左移動の処理
	if (m_pPadState[PAD_LEFT])
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
		if (m_pPadOldState[PAD_LEFT])
		{
			m_CurrentAnima = WALK_SIDE;

		}		
	}


	//右の移動処理
	if (m_pPadState[PAD_RIGHT])
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
		if (m_pPadOldState[PAD_RIGHT])
		{
			m_CurrentAnima = WALK_SIDE;

		}
	}


	//下移動の処理
	if (m_pPadState[PAD_DOWN])
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
		if (m_pPadOldState[PAD_DOWN])
		{
			m_CurrentAnima = WALK_FRONT;

		}
	}


	//上移動の処理
	if (m_pPadState[PAD_UP])
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
		if (m_pPadOldState[PAD_UP])
		{
			m_CurrentAnima = WALK_BACK;

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