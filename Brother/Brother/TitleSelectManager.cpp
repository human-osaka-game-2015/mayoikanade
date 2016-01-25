#include "TitleSelectManager.h"
#include "TitleScene.h"


/**
 * TitleSelectManagerクラスのコンストラクタ
 * @param [in] pLibrary ライブラリクラス
 * @param [in] pPadState GamePadのスティックの状態が格納される
 * @param [in] pPadOldState GamePadのスティックの前の状態が格納される
 * @param [in] pButtonState GamePadのボタンの状態が格納される
 */
TitleSelectManager::TitleSelectManager(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState):
m_pLibrary(pLibrary), 
m_PadState(pPadState), 
m_PadOldState(pPadOldState), 
m_pButtonState(pButtonState),
m_CurrentSelect(GAME_START),
m_alpha(COLORMAX)
{
	m_StartPos.x = STARTPOS_X;
	m_StartPos.y = STARTPOS_Y;
	m_StaffPos.x = STAFFPOS_X;
	m_StaffPos.y = STAFFPOS_Y;
	m_EndPos.x = ENDPOS_X;
	m_EndPos.y = ENDPOS_Y;
	m_CursolPos.w = CURSOL_WIDTH;
	m_CursolPos.h = CURSOL_HEIGHT;

	m_pLibrary->InitAnima(CURSOL_ANIMA);
}


/**
 * TitleSelectManagerクラスのデストラクタ
 */
TitleSelectManager::~TitleSelectManager()
{

}


/**
 * TitleSelectのコントロール関数
 * @return 選択された項目
 */
TITLESELECT_ID TitleSelectManager::Control()
{

	//コントローラーの入力で状態を変更して
	//カーソル位置が変わるようにしている
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


	//Aボタンが押されたら現在指している選択項目を返す
	if (m_pButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		return m_CurrentSelect;
	}

	//通常はTitleSelectNoneを返す
	return TITLESELECT_NONE;
}


/**
 * TitleSelectの描画関数
 */
void TitleSelectManager::Draw()
{
	CustomVertex Start[SQUARE_VERTEX];
	CustomVertex Staff[SQUARE_VERTEX];
	CustomVertex End[SQUARE_VERTEX];
	CustomVertex Cursol[SQUARE_VERTEX];

	//カーソルの位置設定
	switch (m_CurrentSelect)
	{
	case GAME_START:
		m_CursolPos.x = START_CURSOL_POSX;
		m_CursolPos.y = START_CURSOL_POSY;
		break;
	case GAME_STAFF:
		m_CursolPos.x = STAFF_CURSOL_POSX;
		m_CursolPos.y = STAFF_CURSOL_POSY;
		break;
	case GAME_END:
		m_CursolPos.x = END_CURSOL_POSX;
		m_CursolPos.y = END_CURSOL_POSY;
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
		if (m_alpha <= SELECT_ALPHA_MIN)
		{
			m_isSelectFadeout = false;
		}
	}
	else
	{
		m_alpha++;
		if (m_alpha >= SELECT_ALPHA_MAX)
		{
			m_isSelectFadeout = true;
		}
	}
	

	switch (m_CurrentSelect)
	{
	case GAME_START:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			Start[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		break;
	case GAME_STAFF:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			Staff[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		break;
	case GAME_END:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			End[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}


		break;
	}

	//選択項目の描画
	m_pLibrary->DrawTexture(TEX_TITLE, Start);
	m_pLibrary->DrawTexture(TEX_TITLE, Staff);
	m_pLibrary->DrawTexture(TEX_TITLE, End);
	m_pLibrary->DrawTexture(TEX_TITLE, Cursol);
}

