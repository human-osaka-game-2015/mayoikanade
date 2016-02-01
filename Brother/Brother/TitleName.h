#ifndef TITLENAME_H
#define TITLENAME_H

#define TITLENAMEPOS_X 343
#define TITLENAMEPOS_Y 198
#include "Library.h"

class TitleName
{
private:
	Library*			m_pLibrary;
	Position			m_Pos;

public:
	TitleName(Library* pLibrary);
	~TitleName();
	void Control();
	void Draw();

};

#endif