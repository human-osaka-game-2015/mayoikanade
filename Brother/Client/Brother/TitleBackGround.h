#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H

#define TITLEBACKGROUNDPOS_X 686
#define TITLEBACKGROUNDPOS_Y 398
#include "Library.h"


class TitleBackGround
{
private:
	Library*			m_pLibrary;
	Position			m_Pos;

public:
	TitleBackGround(Library* pLibrary);
	~TitleBackGround();
	void Control();
	void Draw();
};


#endif