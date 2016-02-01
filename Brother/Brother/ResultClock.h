#ifndef RESULTCLOCK_H
#define RESULTCLOCK_H

#include "Vertex.h"

#define RESULTCLOCK_FADE_TIME 255			//FadeInが始まる時間
#define RESULTCLOCK_INIT_FADE_TIME 0		//FadeTimeの初期値
#define RESULTCLOCK01_POS_X 1080			//時計上部の座標
#define RESULTCLOCK01_POS_Y 324				//時計上部の座標
#define RESULTCLOCK02_POS_X 1080			//時計中部の座標
#define RESULTCLOCK02_POS_Y 524				//時計中部の座標
#define RESULTCLOCK03_POS_X 1080			//時計下部の座標
#define RESULTCLOCK03_POS_Y 824				//時計下部の座標
#define RESULT_CLEAR_CLOCK_HANDPOSX 1079	//GameClear時の針の位置
#define RESULT_CLEAR_CLOCK_HANDPOSY 523		//GameClear時の針の位置
#define RESULT_OVER_CLOCK_HANDPOSX 640		//GameOver時の針の位置
#define RESULT_OVER_CLOCK_HANDPOSY 270		//GameOver時の針の位置
#define ONE_MINUTE_ANGLE 3					//1分経過した時の短針の角度の増加量
#define HALF_AN_HOUR_ANGLE 15				//30分経過した時の長針の角度の増加量
#define TEN_SECONDS 600						//10秒
#define SIX_HUNDRED_SECONDS 36000			//600秒


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
	void ClearDraw();
	void OverDraw();

#ifdef _DEBUG
	void ClockControl(int Time);
#endif

};





#endif