#ifndef RESULTBACKGROUND_H
#define RESULTBACKGROUND_H

#include "Vertex.h"

#define RESULTBACKGROUND_FADE_TIME 0		//FadeInが始まる時間
#define RESULTBACKGROUND_INIT_FADE_TIME 0	//FadeTimeの初期値
#define RESULTBACKGROUND_POS_X 640			//BackGroundの座標
#define RESULTBACKGROUND_POS_Y 360			//BackGroundの座標


class Library;

class ResultBackGround
{
private:
	Library*	m_pLibrary;
	bool		m_isGameClear;
	int			m_alpha;
	int			m_FadeTime;
	Position	m_BackGroundPos;

public:
	ResultBackGround(Library* pLibrary, bool isGameClear);
	~ResultBackGround();
	void Control();
	void Draw();
	void ClearDraw();
	void OverDraw();

};





#endif