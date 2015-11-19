#include "TitleSelectManager.h"
#include "TitleScene.h"

TitleSelectManager::TitleSelectManager(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture, bool* pPadState, bool* pPadOldState) 
	:m_pLibrary(pLibrary), m_pTexture(pTexture), m_PadState(pPadState), m_PadOldState(pPadOldState), m_CurrentSelect(GAME_START)
{
	m_StartPos.x = STARTPOS_X;
	m_StartPos.y = STARTPOS_Y;
	m_StaffPos.x = STAFFPOS_X;
	m_StaffPos.y = STAFFPOS_Y;
	m_EndPos.x = ENDPOS_X;
	m_EndPos.y = ENDPOS_Y;
	m_CursolPos.w = 100;
	m_CursolPos.h = 130;

	m_pLibrary->InitAnima(CURSOL_ANIMA);
}

TitleSelectManager::~TitleSelectManager()
{

}

TITLESELECT_ID TitleSelectManager::Control()
{

	//コントローラーの入力で状態を変更して
	//カーソル位置なんかが変わるようにしている
	if (m_PadState[ANALOG_UP] == true && m_PadOldState[ANALOG_UP] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_START:
			m_CurrentSelect = GAME_STAFF;

			break;
		case GAME_STAFF:
			m_CurrentSelect = GAME_START;

			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_DOWN] == true && m_PadOldState[ANALOG_DOWN] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_START:
			m_CurrentSelect = GAME_STAFF;

			break;
		case GAME_STAFF:
			m_CurrentSelect = GAME_START;

			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_LEFT] == true && m_PadOldState[ANALOG_LEFT] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_START:
			m_CurrentSelect = GAME_END;

			break;
		case GAME_STAFF:
			m_CurrentSelect = GAME_END;

			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_RIGHT] == true && m_PadOldState[ANALOG_RIGHT] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_END:
			m_CurrentSelect = GAME_START;

			break;
		default:

			break;
		}
	}


	//ボタンが押されたら現在指している選択項目を返す
	if (m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1) == PAD_PUSH)
	{
		return m_CurrentSelect;
	}

	//ボタンが押されなければTitleSelectNoneを返す
	return TITLESELECT_NONE;
}

void TitleSelectManager::Draw()
{
	CustomVertex Start[4];
	CustomVertex Staff[4];
	CustomVertex End[4];
	CustomVertex Cursol[4];

	//カーソルの位置設定
	switch (m_CurrentSelect)
	{
	case GAME_START:
		m_CursolPos.x = STARTPOS_X - 150;
		m_CursolPos.y = STARTPOS_Y - 10;

		break;
	case GAME_STAFF:
		m_CursolPos.x = STAFFPOS_X - 150;
		m_CursolPos.y = STAFFPOS_Y - 10;

		break;
	case GAME_END:
		m_CursolPos.x = ENDPOS_X;
		m_CursolPos.y = ENDPOS_Y - 150;

		break;
	}

	//カーソルのアニメーション
	int CursolId;
	CursolId = m_pLibrary->AnimaControl(m_CursolCurrentAnima);


	//positionの幅高さ設定
	m_pLibrary->MakePosition(TITLE_START, &m_StartPos);
	m_pLibrary->MakePosition(TITLE_STAFF, &m_StaffPos);
	m_pLibrary->MakePosition(TITLE_END, &m_EndPos);


	//tu　tvの設定
	m_pLibrary->MakeVertex(TITLE_START, Start);
	m_pLibrary->MakeVertex(TITLE_STAFF, Staff);
	m_pLibrary->MakeVertex(TITLE_END, End);
	m_pLibrary->MakeVertex(CursolId, Cursol);


	//X yの設定
	m_pLibrary->xySet(m_StartPos, Start);
	m_pLibrary->xySet(m_StaffPos, Staff);
	m_pLibrary->xySet(m_EndPos, End);
	m_pLibrary->xySet(m_CursolPos, Cursol);


	if (m_isSelectFadeout == true)
	{
		m_alpha--;
		if (m_alpha <= 200)
		{
			m_isSelectFadeout = false;
		}
	}
	else
	{
		m_alpha++;
		if (m_alpha >= 255)
		{
			m_isSelectFadeout = true;
		}
	}
	

	switch (m_CurrentSelect)
	{
	case GAME_START:
		for (int i = 0; i < 4; i++)
		{
			Start[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		break;
	case GAME_STAFF:
		for (int i = 0; i < 4; i++)
		{
			Staff[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		break;
	case GAME_END:
		for (int i = 0; i < 4; i++)
		{
			End[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}


		break;
	}

	//描画
	m_pLibrary->Set_Draw_Tex(m_pTexture, Start);
	m_pLibrary->Set_Draw_Tex(m_pTexture, Staff);
	m_pLibrary->Set_Draw_Tex(m_pTexture, End);
	m_pLibrary->Set_Draw_Tex(m_pTexture, Cursol);
}

