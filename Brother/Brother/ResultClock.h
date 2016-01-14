#ifndef RESULTCLOCK_H
#define RESULTCLOCK_H

#include "Vertex.h"

#define RESULTCLOCK_FADE_TIME 255
#define RESULTCLOCK_INIT_FADE_TIME 0
#define RESULTCLOCK01_POS_X 1080
#define RESULTCLOCK01_POS_Y 324
#define RESULTCLOCK02_POS_X 1080
#define RESULTCLOCK02_POS_Y 524
#define RESULTCLOCK03_POS_X 1080
#define RESULTCLOCK03_POS_Y 824


class Library;

class ResultClock
{
private:
	Library*	m_pLibrary;
	bool		m_isGameClear;
	int			m_alpha;
	int			m_FadeTime;
	int			m_GameTime;
	Position	m_Clock01Pos;
	Position	m_Clock02Pos;
	Position	m_Clock03Pos;
	Position	m_ClockLongHandPos;
	Position	m_ClockShortHandPos;


public:
	ResultClock(Library* pLibrary, bool isGameClear,int GameTime);
	~ResultClock();
	void Control();
	void Draw();
#ifdef _DEBUG
	void ClockControl(int Time);
#endif

};





#endif