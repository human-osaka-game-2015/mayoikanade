#include "ResultBackGround.h"
#include "ResultScene.h"
#include "Library.h"


/**
 * ResultBackGroundクラスのコンストラクタ
 * @param [in] pLibrary ライブラリクラス
 * @param [in] isGameClear ゲームクリアしたかのフラグ
 */
ResultBackGround::ResultBackGround(Library* pLibrary, bool isGameClear) :
m_pLibrary(pLibrary),
m_isGameClear(isGameClear),
m_alpha(COLORMIN),
m_FadeTime(RESULTBACKGROUND_INIT_FADE_TIME)
{
	//クリアしたかによって初期化する座標を変更している
	if (m_isGameClear == true)
	{
		m_pLibrary->MakePosition(GAMECLEAR_BACKGROUND, &m_BackGroundPos);
	}
	else
	{
		m_pLibrary->MakePosition(GAMEOVER_BACKGROUND, &m_BackGroundPos);
	}
	
	m_BackGroundPos.x = RESULTBACKGROUND_POS_X;
	m_BackGroundPos.y = RESULTBACKGROUND_POS_Y;
}

/**
 * ResultBackGroundクラスのデストラクタ
 */
ResultBackGround::~ResultBackGround()
{

}

/**
 * ResultBackGroundのコントロール関数
 */
void ResultBackGround::Control()
{
	if (m_FadeTime >= RESULTBACKGROUND_FADE_TIME)
	{
		if (m_alpha < COLORMAX)
		{
			m_alpha++;
		}
		else if (m_alpha > COLORMAX)
		{
			m_alpha = COLORMAX;
		}
	}
	else
	{
		m_FadeTime++;
	}

}

/**
 * ResultBackGroundの描画関数
 */
void ResultBackGround::Draw()
{
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
 * GameClear時の描画関数
 */
void ResultBackGround::ClearDraw()
{
	CustomVertex BackGroundVertex[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMECLEAR_BACKGROUND, BackGroundVertex);

	m_pLibrary->xySet(m_BackGroundPos, BackGroundVertex);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		BackGroundVertex[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_GAMECLEAR, BackGroundVertex);
}

/**
 * GameOver時の描画関数
 */
void ResultBackGround::OverDraw()
{
	CustomVertex BackGroundVertex[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMEOVER_BACKGROUND, BackGroundVertex);

	m_pLibrary->xySet(m_BackGroundPos, BackGroundVertex);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		BackGroundVertex[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_GAMEOVER, BackGroundVertex);
}
