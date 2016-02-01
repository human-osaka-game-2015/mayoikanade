#ifndef STAFFBACKGROUND_H
#define STAFFBACKGROUND_H

#define STAFFBACKGROUNDPOS_X 686
#define STAFFBACKGROUNDPOS_Y 398
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