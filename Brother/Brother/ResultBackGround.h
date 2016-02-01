#ifndef RESULTBACKGROUND_H
#define RESULTBACKGROUND_H

#include "Vertex.h"

#define RESULTBACKGROUND_FADE_TIME 0		//FadeIn���n�܂鎞��
#define RESULTBACKGROUND_INIT_FADE_TIME 0	//FadeTime�̏����l
#define RESULTBACKGROUND_POS_X 640			//BackGround�̍��W
#define RESULTBACKGROUND_POS_Y 512			//BackGround�̍��W


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