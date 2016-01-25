#ifndef TITLETIMEMANAGER_H
#define TITLETIMEMANAGER_H

#define TITLEBLACKOUT_X 640
#define TITLEBLACKOUT_Y 512
#define TITLEBLACKOUT_W 1280
#define	TITLEBLACKOUT_H 1024
#define FADEOUT_TIME 1200

#include "Library.h"

class TitleTimeManager
{
private:
	Library*			m_pLibrary;
	Position			m_Pos;
	unsigned int&		m_GameTime;
	int					m_alpha;

public:
	TitleTimeManager(Library* pLibrary, unsigned int& GameTime);
	~TitleTimeManager();
	bool Control();
	void Draw();
};


#endif