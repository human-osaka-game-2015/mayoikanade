#include "ResultClock.h"
#include "ResultScene.h"
#include "Library.h"


/**
 * ResultClockクラスのコンストラクタ
 * @param [in] pLibrary ライブラリクラス
 * @param [in] isGameClear ゲームをクリアしたかのフラグ
 * @param [in] GameTime GameScene内でどれだけ時間がたったか
 */
ResultClock::ResultClock(Library* pLibrary, bool isGameClear, int GameTime) :
m_pLibrary(pLibrary), 
m_isGameClear(isGameClear),
m_GameTime(GameTime),
m_alpha(COLORMIN),
m_FadeTime(RESULTCLOCK_INIT_FADE_TIME)
{
	//GameClearかGameOverで読み込むファイルと初期化する座標を変えている
	if (m_isGameClear == true)
	{
		//時計の位置の初期化
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK01, &m_Clock01Pos);
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK02, &m_Clock02Pos);
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK03, &m_Clock03Pos);
		m_Clock01Pos.x = RESULTCLOCK01_POS_X;
		m_Clock01Pos.y = RESULTCLOCK01_POS_Y;
		m_Clock02Pos.x = RESULTCLOCK02_POS_X;
		m_Clock02Pos.y = RESULTCLOCK02_POS_Y;
		m_Clock03Pos.x = RESULTCLOCK03_POS_X;
		m_Clock03Pos.y = RESULTCLOCK03_POS_Y;

		//時計の針の座標の初期化
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK_SHORT_HAND, &m_ClockShortHandPos);
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK_LONG_HAND, &m_ClockLongHandPos);
		m_ClockShortHandPos.x = RESULT_CLEAR_CLOCK_HANDPOSX;
		m_ClockShortHandPos.y = RESULT_CLEAR_CLOCK_HANDPOSY;
		m_ClockLongHandPos.x = RESULT_CLEAR_CLOCK_HANDPOSX;
		m_ClockLongHandPos.y = RESULT_CLEAR_CLOCK_HANDPOSY;
	}
	else
	{
		//時計の針の座標の初期化
		m_pLibrary->MakePosition(GAMEOVER_CLOCK_SHORT_HAND, &m_ClockShortHandPos);
		m_pLibrary->MakePosition(GAMEOVER_CLOCK_LONG_HAND, &m_ClockLongHandPos);
		m_ClockShortHandPos.x = RESULT_OVER_CLOCK_HANDPOSX;
		m_ClockShortHandPos.y = RESULT_OVER_CLOCK_HANDPOSY;
		m_ClockLongHandPos.x = RESULT_OVER_CLOCK_HANDPOSX;
		m_ClockLongHandPos.y = RESULT_OVER_CLOCK_HANDPOSY;
	}
}


/**
 * ResultClockクラスのデストラクタ
 */
ResultClock::~ResultClock()
{

}

/**
 * ResultClockのコントロール関数
 */
void ResultClock::Control()
{
	if (m_FadeTime >= RESULTCLOCK_FADE_TIME)
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
 * ResultClockの描画関数
 */
void ResultClock::Draw()
{
	//GameClearかGameOverで読み込むファイルと初期化する座標を変えている
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
void ResultClock::ClearDraw()
{
	CustomVertex ClockVertex01[SQUARE_VERTEX];
	CustomVertex ClockVertex02[SQUARE_VERTEX];
	CustomVertex ClockVertex03[SQUARE_VERTEX];
	CustomVertex ClockShortHand[SQUARE_VERTEX];
	CustomVertex ClockLongHand[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMECLEAR_CLOCK01, ClockVertex01);
	m_pLibrary->MakeVertex(GAMECLEAR_CLOCK02, ClockVertex02);
	m_pLibrary->MakeVertex(GAMECLEAR_CLOCK03, ClockVertex03);
	m_pLibrary->MakeVertex(GAMECLEAR_CLOCK_SHORT_HAND, ClockShortHand);
	m_pLibrary->MakeVertex(GAMECLEAR_CLOCK_LONG_HAND, ClockLongHand);

	m_pLibrary->xySet(m_Clock01Pos, ClockVertex01);
	m_pLibrary->xySet(m_Clock02Pos, ClockVertex02);
	m_pLibrary->xySet(m_Clock03Pos, ClockVertex03);
	m_pLibrary->xySet(m_ClockShortHandPos, ClockShortHand);
	m_pLibrary->xySet(m_ClockLongHandPos, ClockLongHand);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		ClockVertex01[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		ClockVertex02[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		ClockVertex03[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		ClockShortHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		ClockLongHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	int ClockLongHandAngle = (m_GameTime / TEN_SECONDS) * ONE_MINUTE_ANGLE;
	int ClockShortHandAngle = (m_GameTime / SIX_HUNDRED_SECONDS) * HALF_AN_HOUR_ANGLE;

	m_pLibrary->Turn(ClockLongHand, &m_ClockLongHandPos, ClockLongHandAngle);
	m_pLibrary->Turn(ClockShortHand, &m_ClockShortHandPos, ClockShortHandAngle);

	m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockVertex01);
	m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockVertex02);
	m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockVertex03);
	m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockShortHand);
	m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockLongHand);
}


/**
 * GameOver時の描画関数
 */
void ResultClock::OverDraw()
{
	CustomVertex ClockShortHand[SQUARE_VERTEX];
	CustomVertex ClockLongHand[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMEOVER_CLOCK_SHORT_HAND, ClockShortHand);
	m_pLibrary->MakeVertex(GAMEOVER_CLOCK_LONG_HAND, ClockLongHand);

	m_pLibrary->xySet(m_ClockShortHandPos, ClockShortHand);
	m_pLibrary->xySet(m_ClockLongHandPos, ClockLongHand);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		ClockShortHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		ClockLongHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	//ゲーム内で経過した時間
	int ClockLongHandAngle = (m_GameTime / TEN_SECONDS) * ONE_MINUTE_ANGLE;
	int ClockShortHandAngle = (m_GameTime / SIX_HUNDRED_SECONDS) * HALF_AN_HOUR_ANGLE;

	m_pLibrary->Turn(ClockLongHand, &m_ClockLongHandPos, ClockLongHandAngle);
	m_pLibrary->Turn(ClockShortHand, &m_ClockShortHandPos, ClockShortHandAngle);


	m_pLibrary->DrawTexture(TEX_GAMEOVER, ClockShortHand);
	m_pLibrary->DrawTexture(TEX_GAMEOVER, ClockLongHand);
}


#ifdef _DEBUG

/**
 * ResultClockのデバッグ用関数
 * 時計の針を動かせる
 */
void ResultClock::ClockControl(int Time)
{
	m_GameTime += Time;
}

#endif


