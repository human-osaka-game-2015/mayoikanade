#include "ResultText.h"
#include "ResultBackGround.h"
#include "ResultScene.h"
#include "Library.h"


/**
 * ResultTextクラスのコンストラクタ
 * @param [in] pLibrary ライブラリクラス
 * @param [in] isGameClear クリアしたかのフラグ
 */
ResultText::ResultText(Library* pLibrary, bool isGameClear) :
m_pLibrary(pLibrary), 
m_isGameClear(isGameClear),
m_ClearAlpha(COLORMIN),
m_TitleAlpha(COLORMIN),
m_FadeTime(RESULTTEXT_INIT_FADE_TIME),
m_isTextFadeIn(true),
m_isTitleFadeIn(false)
{
	if (m_isGameClear == true)
	{
		m_pLibrary->MakePosition(GAMECLEAR_TITLE_TEXT, &m_TitlePos);
		m_pLibrary->MakePosition(GAMECLEAR_CLEAR_TEXT, &m_ClearPos);

		m_TitlePos.x = RESULTTITLE_POS_X;
		m_TitlePos.y = RESULTTITLE_POS_Y;
		m_ClearPos.x = RESULTCLEAR_POS_X;
		m_ClearPos.y = RESULTCLEAR_POS_Y;
	}
	else
	{
		m_pLibrary->MakePosition(GAMEOVER_TITLE_TEXT, &m_TitlePos);
		m_pLibrary->MakePosition(GAMEOVER_GAMEOVER_TEXT, &m_OverPos);

		m_TitlePos.x = RESULTTITLE_POS_X;
		m_TitlePos.y = RESULTTITLE_POS_Y;
		m_OverPos.x = RESULTOVER_POS_X;
		m_OverPos.y = RESULTOVER_POS_Y;
	}
}

/**
 * ResultTextクラスのデストラクタ
 */
ResultText::~ResultText()
{

}

/**
 * ResultTextのコントロール関数
 */
void ResultText::Control()
{
	//GameClearかGameOverで処理を変える
	if (m_isGameClear == true)
	{
		ClearControl();
	}
	else
	{
		OverControl();
	}

}

/**
　* ResultTextの描画関数
　*/
void ResultText::Draw()
{
	//GameClearかGameOverで処理を変える
	if (m_isGameClear == true)
	{
		ClearDraw();
	}
	else
	{
		OverDraw();
	}

}

/**
 * GameClear時のコントロール関数
 */
void ResultText::ClearControl()
{
	if (m_isTextFadeIn == true)
	{
		if (m_FadeTime >= RESULTTEXT_FADE_TIME)
		{
			if (m_ClearAlpha < COLORMAX)
			{
				m_ClearAlpha++;
				m_TitleAlpha++;
			}
			else if (m_ClearAlpha > COLORMAX)
			{
				m_ClearAlpha = COLORMAX;
				m_TitleAlpha = COLORMAX;
			}
		}
		else
		{
			m_FadeTime++;
		}

		if (m_ClearAlpha == COLORMAX)
		{
			m_isTextFadeIn = false;
		}
	}
	else
	{
		if (m_isTitleFadeIn == true)
		{
			m_TitleAlpha += RESULT_TEXT_FADESPEAD;

			if (m_TitleAlpha == RESULTTITLE_ALPHA_MAX)
			{
				m_isTitleFadeIn = false;
			}
		}
		else
		{
			m_TitleAlpha -= RESULT_TEXT_FADESPEAD;

			if (m_TitleAlpha == RESULTTITLE_ALPHA_MIN)
			{
				m_isTitleFadeIn = true;
			}
		}
	}
}


/**
 * GameOver時のコントロール関数
 */
void ResultText::OverControl()
{
	if (m_isTextFadeIn == true)
	{
		if (m_FadeTime >= RESULTTEXT_FADE_TIME)
		{
			if (m_OverAlpha < COLORMAX)
			{
				m_OverAlpha++;
				m_TitleAlpha++;
			}
			else if (m_OverAlpha > COLORMAX)
			{
				m_OverAlpha = COLORMAX;
				m_TitleAlpha = COLORMAX;
			}
		}
		else
		{
			m_FadeTime++;
		}

		if (m_OverAlpha == COLORMAX)
		{
			m_isTextFadeIn = false;
		}
	}
	else
	{
		if (m_isTitleFadeIn == true)
		{
			m_TitleAlpha += RESULT_TEXT_FADESPEAD;

			if (m_TitleAlpha == RESULTTITLE_ALPHA_MAX)
			{
				m_isTitleFadeIn = false;
			}
		}
		else
		{
			m_TitleAlpha -= RESULT_TEXT_FADESPEAD;

			if (m_TitleAlpha == RESULTTITLE_ALPHA_MIN)
			{
				m_isTitleFadeIn = true;
			}
		}
	}
}


/**
 * GameClear時の描画関数
 */
void ResultText::ClearDraw()
{
	CustomVertex GameClearVertex[SQUARE_VERTEX];
	CustomVertex TitleVertex[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMECLEAR_CLEAR_TEXT, GameClearVertex);
	m_pLibrary->MakeVertex(GAMECLEAR_TITLE_TEXT, TitleVertex);

	m_pLibrary->xySet(m_ClearPos, GameClearVertex);
	m_pLibrary->xySet(m_TitlePos, TitleVertex);


	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		GameClearVertex[i].color = D3DCOLOR_ARGB(m_ClearAlpha, COLORMAX, COLORMAX, COLORMAX);
		TitleVertex[i].color = D3DCOLOR_ARGB(m_TitleAlpha, COLORMAX, COLORMAX, COLORMAX);
	}


	m_pLibrary->DrawTexture(TEX_GAMECLEAR, GameClearVertex);
	m_pLibrary->DrawTexture(TEX_GAMECLEAR, TitleVertex);
}


/**
 * GameOver時の描画関数
 */
void ResultText::OverDraw()
{
	CustomVertex GameOverVertex[SQUARE_VERTEX];
	CustomVertex TitleVertex[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMEOVER_GAMEOVER_TEXT, GameOverVertex);
	m_pLibrary->MakeVertex(GAMEOVER_TITLE_TEXT, TitleVertex);

	m_pLibrary->xySet(m_OverPos, GameOverVertex);
	m_pLibrary->xySet(m_TitlePos, TitleVertex);


	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		GameOverVertex[i].color = D3DCOLOR_ARGB(m_OverAlpha, COLORMAX, COLORMAX, COLORMAX);
		TitleVertex[i].color = D3DCOLOR_ARGB(m_TitleAlpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_GAMEOVER, GameOverVertex);
	m_pLibrary->DrawTexture(TEX_GAMEOVER, TitleVertex);
}
