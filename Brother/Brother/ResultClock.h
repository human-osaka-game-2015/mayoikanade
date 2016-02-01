#ifndef RESULTCLOCK_H
#define RESULTCLOCK_H

#include "Vertex.h"

#define RESULTCLOCK_FADE_TIME 255			//FadeIn���n�܂鎞��
#define RESULTCLOCK_INIT_FADE_TIME 0		//FadeTime�̏����l
#define RESULTCLOCK01_POS_X 1080			//���v�㕔�̍��W
#define RESULTCLOCK01_POS_Y 324				//���v�㕔�̍��W
#define RESULTCLOCK02_POS_X 1080			//���v�����̍��W
#define RESULTCLOCK02_POS_Y 524				//���v�����̍��W
#define RESULTCLOCK03_POS_X 1080			//���v�����̍��W
#define RESULTCLOCK03_POS_Y 824				//���v�����̍��W
#define RESULT_CLEAR_CLOCK_HANDPOSX 1079	//GameClear���̐j�̈ʒu
#define RESULT_CLEAR_CLOCK_HANDPOSY 523		//GameClear���̐j�̈ʒu
#define RESULT_OVER_CLOCK_HANDPOSX 640		//GameOver���̐j�̈ʒu
#define RESULT_OVER_CLOCK_HANDPOSY 270		//GameOver���̐j�̈ʒu
#define ONE_MINUTE_ANGLE 3					//1���o�߂������̒Z�j�̊p�x�̑�����
#define HALF_AN_HOUR_ANGLE 15				//30���o�߂������̒��j�̊p�x�̑�����
#define TEN_SECONDS 600						//10�b
#define SIX_HUNDRED_SECONDS 36000			//600�b


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