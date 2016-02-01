#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H

#define TITLEBACKGROUNDPOS_X 640
#define TITLEBACKGROUNDPOS_Y 512
#include "Library.h"


class TitleBackGround
{
private:
	Library*			m_pLibrary;
	Position			m_Pos;

public:
	TitleBackGround(Library* pLibrary);
	~TitleBackGround();
	void Draw();
};


#endif