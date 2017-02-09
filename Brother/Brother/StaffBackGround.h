#ifndef STAFFBACKGROUND_H
#define STAFFBACKGROUND_H

#define STAFFBACKGROUNDPOS_X 640
#define STAFFBACKGROUNDPOS_Y 360
#include "Library.h"

class StaffBackGround
{
private:
	Library*				m_pLibrary;
	Position				m_Pos;


public:
	StaffBackGround(Library* pLibrary);
	~StaffBackGround();
	void Draw();

};



#endif