#include "ResultClock.h"
#include "ResultScene.h"
#include "Library.h"



ResultClock::ResultClock(Library* pLibrary, bool isGameClear, int GameTime) :
m_pLibrary(pLibrary), 
m_isGameClear(isGameClear),
m_GameTime(GameTime),
m_alpha(COLORMIN),
m_FadeTime(RESULTCLOCK_INIT_FADE_TIME)
{
	m_pLibrary->MakePosition(GAMECLEAR_CLOCK01, &m_Clock01Pos);
	m_pLibrary->MakePosition(GAMECLEAR_CLOCK02, &m_Clock02Pos);
	m_pLibrary->MakePosition(GAMECLEAR_CLOCK03, &m_Clock03Pos);
	
	m_Clock01Pos.x = RESULTCLOCK01_POS_X;
	m_Clock01Pos.y = RESULTCLOCK01_POS_Y;
	m_Clock02Pos.x = RESULTCLOCK02_POS_X;
	m_Clock02Pos.y = RESULTCLOCK02_POS_Y;
	m_Clock03Pos.x = RESULTCLOCK03_POS_X;
	m_Clock03Pos.y = RESULTCLOCK03_POS_Y;


	if (m_isGameClear == true)
	{
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK_SHORT_HAND, &m_ClockShortHandPos);
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK_LONG_HAND, &m_ClockLongHandPos);

		m_ClockShortHandPos.x = 1080;
		m_ClockShortHandPos.y = 524;
		m_ClockLongHandPos.x = 1080;
		m_ClockLongHandPos.y = 524;
	
	}
	else
	{
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK_SHORT_HAND, &m_ClockShortHandPos);
		m_pLibrary->MakePosition(GAMECLEAR_CLOCK_LONG_HAND, &m_ClockLongHandPos);

		m_ClockShortHandPos.x = 640;
		m_ClockShortHandPos.y = 270;
		m_ClockLongHandPos.x = 640;
		m_ClockLongHandPos.y = 270;
	}
}


ResultClock::~ResultClock()
{

}


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

void ResultClock::Draw()
{
	if (m_isGameClear == true)
	{
		CustomVertex ClockVertex01 [SQUARE_VERTEX];
		CustomVertex ClockVertex02 [SQUARE_VERTEX];
		CustomVertex ClockVertex03 [SQUARE_VERTEX];
		CustomVertex ClockShortHand[SQUARE_VERTEX];
		CustomVertex ClockLongHand [SQUARE_VERTEX];


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


		for (int i = 0; i < SQUARE_VERTEX; i++)
		{
			ClockVertex01[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
			ClockVertex02[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
			ClockVertex03[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
			ClockShortHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
			ClockLongHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);

		}
		
		int ClockLongHandAngle = m_GameTime / 600 * 3;
		int ClockShortHandAngle = m_GameTime / 36000 * 15;

		m_pLibrary->Turn(ClockLongHand, &m_ClockLongHandPos, ClockLongHandAngle);
		m_pLibrary->Turn(ClockShortHand, &m_ClockShortHandPos, ClockShortHandAngle);


		m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockVertex01);
		m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockVertex02);
		m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockVertex03);
		m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockShortHand);
		m_pLibrary->DrawTexture(TEX_GAMECLEAR, ClockLongHand);

	}
	else
	{
		CustomVertex ClockShortHand[SQUARE_VERTEX];
		CustomVertex ClockLongHand[SQUARE_VERTEX];

		m_pLibrary->MakeVertex(GAMEOVER_CLOCK_SHORT_HAND, ClockShortHand);
		m_pLibrary->MakeVertex(GAMEOVER_CLOCK_LONG_HAND, ClockLongHand);

		m_pLibrary->xySet(m_ClockShortHandPos, ClockShortHand);
		m_pLibrary->xySet(m_ClockLongHandPos, ClockLongHand);

		for (int i = 0; i < SQUARE_VERTEX; i++)
		{
			ClockShortHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
			ClockLongHand[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		m_pLibrary->DrawTexture(TEX_GAMEOVER, ClockShortHand);
		m_pLibrary->DrawTexture(TEX_GAMEOVER, ClockLongHand);
	}
}


