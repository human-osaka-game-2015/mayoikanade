#ifndef LOGOBACKGROUND_H
#define LOGOBACKGROUND_H

#define LOGOBACKGROUNDPOS_X 686
#define LOGOBACKGROUNDPOS_Y 398
#include "Library.h"

class LogoBackGround
{
private:
	Library*			m_pLibrary;
	Position			m_Pos;
	int					m_alpha;
	bool				m_isFadeIn;

public:
	LogoBackGround(Library* pLibrary);
	~LogoBackGround();

	bool Control();
	void Draw();

};

#endif